#include <LWiFi.h>
#include "MCS.h"
#include "DHT.h"

int t;
int h;

char _lwifi_ssid[] = "basstomouth";
char _lwifi_pass[] = "peter1224";

MCSDevice mcs("DeKxX1KO", "9RO0PaUX0npSfzl8");
MCSDisplayInteger temp("temp");
MCSDisplayInteger humid("humid");

DHT __dht2(4, DHT11);

void setup()
{
  Serial.begin(9600);

  mcs.addChannel(temp);
  mcs.addChannel(humid);
  Serial.println("Wi-Fi start");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("Wi-Fi ok");
  while(!mcs.connected()) { mcs.connect(); }
  Serial.println("MCS ok");
  Serial.begin(9600);
  __dht2.begin();
}

void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) { Serial.println("MCS restart"); }
  }
  mcs.process(100);

  t = __dht2.readTemperature();
  h = __dht2.readHumidity();
  temp.set(t);
  humid.set(h);

  Serial.print("c : ");
  Serial.println(t);
  Serial.print("relative temp :");
  Serial.println(h);

  delay(1000);
}
