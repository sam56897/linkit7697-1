#include <LWiFi.h>
#include "MCS.h"
#include "DHT.h"

int t;
int h;

char _lwifi_ssid[] = "ANCIENT";
char _lwifi_pass[] = "11111111";

MCSDevice mcs("D3iAIkU5", "kL90f3OI9pr9XtZQ");
MCSDisplayInteger temp("temp");
MCSDisplayInteger humid("humid");
MCSControllerOnOff MySwitch("MySwitch");

DHT __dht2(4, DHT11);

void setup()
{
  Serial.begin(9600);

  mcs.addChannel(temp);
  mcs.addChannel(humid);
  mcs.addChannel(MySwitch); //通道id
  Serial.println("Wi-Fi 開始連線");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("Wi-Fi 連線成功");
  while(!mcs.connected()) { mcs.connect(); }
  Serial.println("MCS 連線成功");
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  __dht2.begin();
}

void loop()
{
  while (!mcs.connected()) {
  	mcs.connect();
  	if (mcs.connected()) { Serial.println("MCS 已重新連線"); }
  }
  mcs.process(100);

  t = __dht2.readTemperature();
  h = __dht2.readHumidity();
  temp.set(t);
  humid.set(h);

  Serial.print("攝氏溫度 : ");
  Serial.println(t);
  Serial.print("相對溼度 :");
  Serial.println(h);

  if (MySwitch.updated() || t > 27){
    Serial.print("開啟風扇降溫");
    Serial.println(MySwitch.value());

    if (MySwitch.value()|| t > 27) {
      digitalWrite(LED_BUILTIN, HIGH);

    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  delay(1000);
}

