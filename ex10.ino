#include <DHT.h>
#include <LiquidCrystal_I2C.h>

DHT dht(4, DHT11);
LiquidCrystal_I2C lcd_i2c(0x27);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  lcd_i2c.begin(16, 2);
  pinMode(3, INPUT);
  lcd_i2c.clear();
}

void loop()
{
  Serial.print("溫度=");
  Serial.println(dht.readTemperature());
  Serial.print("濕度=");
  Serial.println(dht.readHumidity());
  Serial.print("土壤濕度=");
  Serial.println(analogRead(14));
  
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print("T=");
  lcd_i2c.setCursor(2,0);
  lcd_i2c.print(dht.readTemperature());
  lcd_i2c.setCursor(8,0);
  lcd_i2c.print("H=");
  lcd_i2c.setCursor(10,0);
  lcd_i2c.print(dht.readHumidity());

  lcd_i2c.setCursor(0,1);
  lcd_i2c.print("SM=");
  lcd_i2c.setCursor(3,1);
  lcd_i2c.print(analogRead(14));
  
  delay(1000);
}
