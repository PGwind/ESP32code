const byte LED = 4;
const byte BUTTON = 25;

// ISR
// IRAM_ATTR 将函数加载到IRAM中，从而提高函数的执行速度和响应性能
IRAM_ATTR void switchPressed()
{
  // 按钮松开高电平亮，按钮按下低电平灭
  if (digitalRead(BUTTON) == HIGH)
    digitalWrite(LED, HIGH);
  else 
    digitalWrite(LED, LOW);
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  // 设置和执行ISR（中断服务程序）
  attachInterrupt(digitalPinToInterrupt(BUTTON), switchPressed, CHANGE);
}

void loop() {

}
