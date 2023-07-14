#include "LiquidCrystal_I2C.h" // 包含 LiquidCrystal_I2C 库，用于LCD显示器
// 共享变量
volatile unsigned long raiseTime = 0; // 前一次上升沿时间
volatile unsigned long fallTime = 0; // 前一次下降沿时间
volatile double duty = 0; // 占空比
volatile double fre = 0; // 频率

int pwmPin = 27; // 信号输入接口

// 显示器初始化
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 自旋锁
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

// ISR：中断服务程序
void changeISR()
{
  auto now = micros();
  if (digitalRead(pwmPin)) // 现在是高
  {
    /*
     临界区是一段代码片段，用于在多任务环境下保护共享资源，以确保对资源的访问不会被并发任务中断或干扰。
     临界区的作用是提供一种互斥机制，使得同一时间只有一个任务可以访问共享资源，避免并发访问导致的数据竞争和不一致性。
    */
    portENTER_CRITICAL_ISR(&mux); // 进入临界区
    auto total = now - raiseTime; // 周期 us
    fre = 1e6 / (double)total; // 频率
    auto h = fallTime - raiseTime; // 脉宽
    duty = h / (double)total; // 占空比 = 脉宽 / 周期
    portEXIT_CRITICAL_ISR(&mux); // 离开临界区
    raiseTime = now;
  }
  else
  {
    fallTime = now;
  }
}

void setup() { 
 lcd.init(); // 初始化 LCD 显示器
  lcd.backlight(); // 打开背光
  lcd.setCursor(0, 0); // 设置光标位置为第一行第一列
  lcd.print("fre: "); // 在 LCD 上打印 "fre: "
  lcd.setCursor(0, 1); // 设置光标位置为第二行第一列
  lcd.print("duty: "); // 在 LCD 上打印 "duty: "
  pinMode(pwmPin, INPUT); // 将 pwmPin 设置为输入模式
  attachInterrupt(digitalPinToInterrupt(pwmPin), changeISR, CHANGE); // 注册中断服务程序来响应 pwmPin 引脚状态变化的事件
}

void loop() {
  delay(1000); // 延迟1秒

  portENTER_CRITICAL(&mux); // 进入临界区
  double f = fre; // 读取频率值
  double d = duty; // 读取占空比值
  portEXIT_CRITICAL(&mux); // 离开临界区

  lcd.setCursor(5, 0); // 设置光标位置为第一行第五列
  lcd.print(f); // 在 LCD 上打印频率值
  lcd.setCursor(6, 1); // 设置光标位置为第二行第六列
  lcd.print(d); // 在 LCD 上打印占空比值
}
