// 两个舵机反转
#include <ESP32Servo.h>

Servo servo1; // 定义对象
Servo servo2;

int minUs = 500; // 0°时的脉宽，单位us
int maxUs = 2500; // 180°时的脉宽，单位us

int servo1Pin = 15;
int servo2Pin = 16;
int pos = -1; // 舵机角度
bool up = true; // 计数方向

void setup() {
  ESP32PWM::allocateTimer(1); // 指定使用的硬件定时器

  servo1.setPeriodHertz(50); // 指定PWM的频率
  servo2.setPeriodHertz(50); // 指定PWM的频率

  servo1.attach(servo1Pin, minUs, maxUs);
  servo2.attach(servo2Pin, minUs, maxUs);

}

void loop() {
  if (pos == 181)
    up = false;
  else if (pos == -1)
    up = true;
  
  if (up)
    pos ++;
  else
    pos --;
  
  servo1.write(pos);
  servo2.write(180 - pos);

  //servo1.write(pos); // 转到指定的角度(0° - 180°)
  //servo1.detach(); // 不需要的时候将引脚和ledc分离

  delay(15);
}
