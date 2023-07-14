/* ADC + LEDC + 定时器(软件)
  通过更改定位器阻值控制LED亮度
*/
#include <AsyncTimer.h>

int pmPin = 32; // 电位器GPIO接口
int ledPin = 4; // LED
int ch0 = 0; // ledc通道

AsyncTimer timer;
int taskId = 0;

void ChangeLedLightness()
{
  int val = analogRead(pmPin); // ADC值
  Serial.printf("%d:", val);

  auto vol = analogReadMilliVolts(pmPin); // 电压值：毫伏值
  Serial.println(vol);

  int duty = val / 4095.0 * 1024;
  ledcWrite(ch0, duty);
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // 确定analogRead() 函数返回的值的分辨率(以位为单位)
  analogSetAttenuation(ADC_11db); // 设置所有通道衰减值

  ledcSetup(ch0, 1000, 10); // 设置ledc通道0，频率1000HZ，精度10
  ledcAttachPin(ledPin, ch0); 

  taskId = timer.setInterval(ChangeLedLightness, 20); //周期定时任务
}

void loop() {
  timer.handle();
}
