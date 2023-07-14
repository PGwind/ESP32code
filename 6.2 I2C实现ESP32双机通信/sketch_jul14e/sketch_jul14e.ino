/* 
  主机每秒2秒向从机发送递增的数字，
  从机在收到主机的数据后LED闪烁0.5秒,并在收到的数字后加上OK字符发送给主机
  主机收到从机发来的数据后打印在串口上
*/

// 主机程序
#include <Wire.h>

int num = 1; // 发送给从机
int address = 33; // 从机地址

void setup() {
  Serial.begin(115200);

  if (Wire.begin()) // 主机加入I2C总线
    Serial.println("I2C Success");
  else 
    Serial.println("I2C Failed");
}

void loop() {
  char tmp[32];
  itoa(num++, tmp, 10); // 将数字转换成字符串

  Wire.beginTransmission(address);
  Wire.write(tmp); // 传输数字字符串
  int ret = Wire.endTransmission();
  if (ret != 0) // 判断状态
  {
    Serial.printf("Send failed：%d\r\n", ret);
    return;
  }

  delay(100); // 从机处理时间

/*
  Wire.requestFrom(address, quantity, stop);
  requestFrom返回值代表了从机发来多少字节的数据，实际上是错误的，
  返回值永远是等于你传进去的欲读取数据的数量值(quantity)
  若 接收的数据量 > 从机发送的数据量，超出部分全部为 0x3f
*/
  int len = Wire.requestFrom(address, 32); // 发出请求，最多不超过32字节
  if (len > 0)
  {
    // 打印出来收到从机发来的数据
    Serial.print("Receive data size:");
    Serial.println(len);

    Wire.readBytes(tmp, 32);
    Serial.println(tmp);

    // 打印出收到数据的16进制值
    for (int i=0; i<32; i++)
    {
      Serial.printf("%2x, ", tmp[i]);
      if (i % 8 == 7)
        Serial.println();
    }
    Serial.println();
  }
  delay(1900);
}
