#include <AsyncTimer.h>

AsyncTimer t; //定义一个定时器

void myfun()
{
  Serial.println("the second");
}
void setup() {
  Serial.begin(115200);
  delay(200);

  //setTimeout(回调函数, 超时时间(ms))，回调函数可以无参无返回值
  auto id = t.setTimeout([](){ //第一个单次定时任务：2s 打印 the first
    Serial.println("the first");
  }, 2000);
  Serial.print("First：");
  Serial.println(id);

  id = t.setTimeout(myfun, 4000); //第二个单词定时任务：4s 打印 the second
  Serial.print("Second：");
  Serial.println(id);
}

void loop() {
  t.handle(); //执行有关定时器的操作，精度与loop()函数里面操作时间有关
}
