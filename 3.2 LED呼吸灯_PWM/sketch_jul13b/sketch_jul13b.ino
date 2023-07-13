/* 每秒钟固定调整占空比50次。T为呼吸周期，光从灭到最亮经过半个周期T/2。
   半个周期进行 50*T/2 调整占空比
   count表示占空比为100%时等分的格子
   step为每次调整时要加上的增量  step = count / (50 * T/2) = 2 * count / (50 * T)
*/

int gpio4 = 4;
int ch1 = 1; //ledc通道号
int duty = 0; //目前信号的占空比
int count = 0; //100%占空比时的格子
int step = 0; //占空比步进值(增量)
int breathTime = 3; //呼周期，单位s

void setup() {
  ledcSetup(ch1, 1000, 12); //建立ledc通道
  count = pow(2, 12); //计算占空比为100%时共几份
  step = 2 * count / (50 * breathTime); //计算一次增加多少格子
  ledcAttachPin(gpio4, ch1); //绑定 ch1 和 GPIO4
}

void loop() {
  ledcWrite(ch1, duty);
  duty += step;
  if (duty > count)
  {
    duty = count;
    step = -step; //step变为负数，duty递减
  } 
  else if (duty < 0)
  {
    duty = 0;
    step = -step; //step变为正数数，duty递增
  }
  delay(20); //阻塞
}
