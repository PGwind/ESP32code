#include <AsyncTimer.h>

AsyncTimer t;

void myfun()
{
  Serial.println("the second");
}

void setup() {
  Serial.begin(115200);
  delay(200);
  
  //setInterval(回调函数, 超时时间(ms))，回调函数可以无参无返回值
  auto id = t.setInterval([](){ //第一个周期定时任务：每 2s 打印 the first
    Serial.println("the first");
  }, 2000);
  Serial.print("First：");
  Serial.println(id);

  id = t.setInterval(myfun, 4000); //第二个周期定时任务：每 4s 打印 the second
  Serial.print("Second：");
  Serial.println(id);
}

void loop() {
  t.handle();
}
