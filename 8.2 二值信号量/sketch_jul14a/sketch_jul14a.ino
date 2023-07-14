// 每 1s 打印一次当前迭代数和时间
#include <esp32-hal-timer.h>
volatile int count = 0;
volatile unsigned long tim = 0;
volatile SemaphoreHandle_t timerSemaphore; // 信号量

hw_timer_t *timer1 = NULL; // 1s 1次
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// ISR
void IRAM_ATTR onTimer1() {
  portENTER_CRITICAL_ISR(&timerMux); // 进入临界区
  count ++;
  tim = micros();
  portEXIT_CRITICAL_ISR(&timerMux); // 离开临界区

  /*
    从中断服务程序（ISR）中给予一个二值信号量它会将二值信号量的计数值增加，
    并唤醒等待该信号量的任务。第二个参数为 NULL 表示不需要唤醒任何任务。
  */
  // 设置完共享变量后发送信号 
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

void setup() {
  Serial.begin(115200);

  timerSemaphore = xSemaphoreCreateBinary(); // 创建一个二值信号量
  // 初始化定时器，80分频，1us计数一次
  timer1 = timerBegin(0, 80, true);
  // 附加中断
  timerAttachInterrupt(timer1, onTimer1, true);
  // 计数到 1000000（1s） 时触发中断
  timerAlarmWrite(timer1, 1000000, true);
  // 开启定时器
  timerAlarmEnable(timer1);
}

void loop() {
  if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
  {
    portENTER_CRITICAL(&timerMux);
    auto c = count;
    auto t = tim;
    portEXIT_CRITICAL(&timerMux);

    Serial.println(c);
    Serial.println(t);
  }
  
}