void setup() {
  int ret = 0;
  Serial.begin(115200);
  int ch0 = 0;
  int gpio4 = 4;
  ret = ledcSetup(ch0, 5000, 12); //设置ledc通道0，频率5000HZ，精度12 

  delay(200);
  if (ret == 0)
    Serial.println("Error Setup");
  else 
    Serial.println("Success Setup");
    
  ledcAttachPin(gpio4, ch0); //设置引脚和通道
  ledcWrite(ch0, pow(2, 11)); //占空比50%   2^11 / 2^12 = 1/2 

}

void loop() {
  // put your main code here, to run repeatedly:

}
