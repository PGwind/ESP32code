/* 
  主机每秒2秒向从机发送递增的数字，
  从机在收到主机的数据后LED闪烁0.5秒,并在收到的数字后加上OK字符发送给主机
  主机收到从机发来的数据后打印在串口上
*/

// 从机程序
#include <Wire.h>
#include <AsyncTimer.h>

char buf[32]; // 接受缓冲区
int ledPin = 4;

AsyncTimer timer;

void onReceive(int len) {
  // 接受数据，将数字存到缓冲区，并让led闪烁
  if (len > 0)
  {
    // 从I2C总线读取最多32个字节的数据，并将其存储到buf缓冲区中。函数返回实际读取到的字节数
    int sz = Wire.readBytes(buf, 32);
    if (sz > 0)
    {
      buf[sz] = 0;
      digitalWrite(ledPin, HIGH);

      // 注册定时事件，500ms后关闭led灯
      timer.setTimeout([](){
        digitalWrite(ledPin, LOW);
      }, 500);
    }
  }
}

void onRequest() {
   // 向主机发送数据
  strcat(buf, "OK"); // 拼接
  Wire.write(buf); // 发送缓冲区数据（包括"OK"字符）
  Wire.write(0);
}
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT); 
  Wire.onReceive(onReceive); // 注册接受事件
  Wire.onRequest(onRequest); // 注册发送事件
  Wire.begin(33);
}

void loop() { 
 timer.handle();
}
