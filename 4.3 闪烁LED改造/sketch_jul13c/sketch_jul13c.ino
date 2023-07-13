// LED灯刚启动以1s周期进行闪烁，按键按下去后在1s和3s的周期进行切换
#include <RBD_Button.h>
#include <AsyncTimer.h>

int switchPin = 25; // 按钮
int ledPin = 4; // led
int ledStatus = HIGH;
int t = 1; // 闪烁周期

//软件消抖
RBD::Button button(switchPin, INPUT_PULLUP);

AsyncTimer timer;
int taskId = 0;

void ChangeLedStatus()
{
  ledStatus = !ledStatus;
  digitalWrite(ledPin, ledStatus);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // 点亮
  button.setDebounceTimeout(20);
  //创建周期任务
  taskId = timer.setInterval(ChangeLedStatus, t*1000);
}

void loop() {
  timer.handle();

  if (button.onPressed())
  {
    t = t == 1?3:1; //周期定时时间为：1s或3s
    timer.changeDelay(taskId, t*1000);
  }
}
