// 中断测距
/* - 将 外部中断(change) 附加到 ECHO 的引脚上
- 使用硬件定时器每 500ms 给 Trigger 一个 15us  的脉冲 （1s测量2次）
- 在上升沿中断的时候记当前时间 t1 
- 在下降沿中断的时候记当前时间 t2，并发 信号(Semaphore)`  给任务
- Loop函数在收到信号后获取 t2和t1 的值，并计算出距离
*/

const int trigPin = 4;
const int echoPin = 16;
double distance = 0; // 单位cm

hw_timer_t *timer1 = NULL; // 定时器
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED; // 自旋锁
volatile unsigned long startTime = 0; // 发出超声波时间
volatile unsigned long endTime = 0; // 收到超声波时间
volatile SemaphoreHandle_t semaphore; // 信号量

// 硬件定时器ISR
void IRAM_ATTR ping()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
}

// ECHO 引脚ISR
void IRAM_ATTR changeISR() 
{
  auto now = micros(); // 当前时间
  auto state = digitalRead(echoPin);

  portENTER_CRITICAL_ISR(&mux);
  if (state) // 高电平，即刚发出超声波
    startTime = now;
  else
    endTime = now;
  portEXIT_CRITICAL_ISR(&mux);

  // 变成低电平时表示已经收到回声
  if (!state)
    xSemaphoreGiveFromISR(semaphore, NULL); // 给一个信号量发送信号
}


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);

  semaphore = xSemaphoreCreateBinary(); // 创建二值信号量

  // 定时器部分
  timer1 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer1, ping, true);
  timerAlarmWrite(timer1, 500000, true); // 定时时间为 0.5s
 
  // echo引脚的中断
  attachInterrupt(digitalPinToInterrupt(echoPin), changeISR, CHANGE);

  // 开始周期测量
  timerAlarmEnable(timer1);

}

void loop() {
  if (xSemaphoreTake(semaphore, 0) == pdTRUE)
  {
    // 收到信号，准备工作
    portENTER_CRITICAL(&mux);
    auto t = endTime - startTime;
    portEXIT_CRITICAL(&mux);

    double dis = t * 0.01715;
    if (dis < 350)
    {   
        distance = dis;
        Serial.print("Distance: "); 
        Serial.print(distance, 1); // 小数点后1位
        Serial.println(" cm");
    }
  }
}
 