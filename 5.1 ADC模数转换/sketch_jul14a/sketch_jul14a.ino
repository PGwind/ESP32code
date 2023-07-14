void setup() {
  Serial.begin(115200);
  analogReadsolution(12); // 设置读取精度（位宽）

  //设置通道衰减值（不设置默认为11db）
  /*
  analogSetAttenuation(ADC_ATTEN_DB_11); // 设置所有通道
  analogSetPinAttenuation(2, ADC_ATTEN_DB_11); // 设置指定GPIO口的衰减值
  */
}

void loop() {
  int analogValue = analogRead(2); // 读取DAC值
  int analogVolts = analogReadMilliVolts(2); // 读取电压值（毫伏值）

  Serial.printf("ADC analog value = %d\n", analogValue);
  Serial.printf("ADC millivolts value = %d\n", analogVlots);

  delay(100);
}
