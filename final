#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27);
// #include <SeeedOLED.h>
#include <LWiFi.h>
#include "MCS.h"

int h; //humidity
int t; //temperature
int s; //soil moisture
int w; //water
int f; //fan
int th = 28;
char ss[3];

char _lwifi_ssid[] = "lita";
char _lwifi_pass[] = "0911027768";

MCSDevice mcs("DCt3P2k3", "YDlnFu0n6Qz8P50U");
MCSDisplayInteger temp("temp");
MCSDisplayInteger humid("humid");
MCSDisplayInteger soil("soil");
MCSControllerOnOff sw1("sw1");
MCSControllerOnOff sw2("sw2");
MCSControllerAnalog fant("fant");

DHT __dht2(2, DHT11);

void setup()
{
  Serial.begin(9600);
  mcs.addChannel(humid);
  mcs.addChannel(temp);
  mcs.addChannel(soil);
  mcs.addChannel(sw1);
  mcs.addChannel(sw2);
  mcs.addChannel(fant);
  Serial.println("Wi-Fi 開始連線");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("Wi-Fi 連線成功");
  while(!mcs.connected()) { mcs.connect(); }
  Serial.println("MCS 連線成功");
  Serial.begin(9600);
  __dht2.begin();
  Wire.begin();
  lcd.begin(16, 2);
  lcd.clear();
/*
  SeeedOled.init();
  SeeedOled.deactivateScroll();
  SeeedOled.setPageMode();
  SeeedOled.clearDisplay();
 */
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
}


void loop()
{
  while (!mcs.connected()) mcs.connect();
  mcs.process(100);
  h = __dht2.readHumidity();
  t = __dht2.readTemperature();
  s = analogRead(A2)/20;
  if (s > 100) s = 100;
  humid.set(h);
  temp.set(t);
  soil.set(s); 
  
  if (sw1.updated()) {
    Serial.print("water :");
    Serial.println(sw1.value());
    if (sw1.value()) {w = 1;
        } else {w = 0;}
  }      
  if (sw2.updated()) {
    Serial.print("fan :");
    Serial.println(sw2.value());
    if (sw2.value()) {f = 1;
        } else {f = 0;}
  }
  if (fant.updated()) {
    Serial.print("fant :");
    Serial.println(fant.value());
    th = fant.value();
  }
    
  if (s <= 50 || w == 1 ) {
    for (int i=0; i <= 2; i++){
      digitalWrite(10, HIGH);
      delay(100);
      digitalWrite(10, LOW);
      delay(100);
   }
  }
  if (s > 50 &&  w== 0 ) {digitalWrite(10, LOW); delay(1000);}
  if (t >= th || f == 1 ) digitalWrite(12, HIGH);
  if (t < th && f == 0 ) digitalWrite(12, LOW);
  Serial.print("相對溼度 : "); Serial.println(h);
  Serial.print("攝氏溫度 : "); Serial.println(t);
  Serial.print("土壤溼度 : "); Serial.println(s);
  lcd.setCursor(0, 0);
  lcd.print("T=");
  lcd.setCursor(2, 0);
  lcd.print(t);
  lcd.setCursor(4, 0);
  lcd.print((char)223);
  lcd.setCursor(5, 0);
  lcd.print("C HUMID=");
  lcd.setCursor(13, 0);
  lcd.print(h);
  lcd.setCursor(15, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("SOIL MOIST=");
  sprintf(ss, "%3d", s);
  lcd.setCursor(11, 1);
  lcd.print(ss);
  lcd.setCursor(14, 1);
  lcd.print("%");
 
/*
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putString("Humidity: ");
  SeeedOled.putNumber(h);
  SeeedOled.setTextXY(2, 0);
  SeeedOled.putString("Temperatue: ");
  SeeedOled.putNumber(t);
  SeeedOled.setTextXY(4, 0);
  SeeedOled.putString("Soil moist: ");
  SeeedOled.putNumber(s);
*/
}
