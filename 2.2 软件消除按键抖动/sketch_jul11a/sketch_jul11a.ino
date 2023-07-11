#include <RBD_Timer.h>
#include <RBD_Button.h>

int switchPin = 25;
int ledPin = 4;
int ledStatus = 0; //LOW

//创建一个可以消除拉动的按键对象
RBD::Button button(switchPin, INPUT_PULLUP); //上拉输入

void setup() {
  pinMode(ledPin, OUTPUT);
  button.setDebounceTimeout(20); // 消除抖动时间是20ms
  digitalWrite(ledPin, HIGH);
  ledStatus = HIGH;
}

void loop() {
  //检测按键按下去的事件(下降沿)
  if (button.onPressed()) //按键已经按下
  {
    ledStatus = !ledStatus;
    digitalWrite(ledPin, ledStatus);
  }
}
