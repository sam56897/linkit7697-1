#include <DHT.h>
#include <LiquidCrystal_I2C.h>

DHT dht(4, DHT11);
LiquidCrystal_I2C lcd_i2c(0x27);
int t;
int h;
int s;
char ss[3];

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
  t = dht.readTemperature();
  h = dht.readHumidity();
  s = analogRead(14);
  s = 100 - map(s, 281,4095, 0, 100);
  sprintf(ss, "%3d", s);
  
  Serial.print("溫度=");
  Serial.println(t);
  Serial.print("濕度=");
  Serial.println(h);
  Serial.print("土壤濕度=");
  Serial.println(s);
  
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print("T=");
  lcd_i2c.setCursor(2,0);
  lcd_i2c.print(t);
  lcd_i2c.setCursor(4,0);
  lcd_i2c.print((char)223);
  lcd_i2c.setCursor(5,0);
  lcd_i2c.print("C Humid=");
  lcd_i2c.setCursor(13,0);
  lcd_i2c.print(h);
  lcd_i2c.setCursor(15,0);
  lcd_i2c.print("%");
  lcd_i2c.setCursor(0,1);
  lcd_i2c.print("Soil Moist=");
  lcd_i2c.setCursor(11,1);
  lcd_i2c.print(ss);
  lcd_i2c.setCursor(14,1);
  lcd_i2c.print("%");
  
  delay(1000);
}
