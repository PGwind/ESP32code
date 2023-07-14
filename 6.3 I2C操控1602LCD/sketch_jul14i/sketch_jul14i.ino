#include <Arduino.h>
#include <Wire.h>
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // LiquidCrystal_I2C lcd(显示器地址, 行数, 列数);

void setup() {
  lcd.init(); // 初始化 LCD 显示器
  lcd.backlight(); // 打开背光
  lcd.print("Hello World!"); // 在第一行打印 "Hello World!"
  // lcd.setCursor(列号, 行号)
  lcd.setCursor(0, 1); // 设置光标位置为第二行第一列
  lcd.print("I am a fish, I am a fish, I am a fish."); // 在第二行打印 "I am a fish, I am a fish, I am a fish."

  // 将第二行的 "am" 改成大写 "AM"
  lcd.setCursor(2, 1); // 设置光标位置为第二行第三列
  lcd.write('A'); // 写入大写字母 'A'
  lcd.write('M'); // 写入大写字母 'M'

  lcd.clear(); // 清空显示器

  // 字幕不停向左滚动
  for (int i = 0; i < 100; i++) {
    lcd.scrollDisplayLeft(); // 向左滚动显示内容
    delay(1000); // 延迟1秒
  }
}

void loop() {

}
