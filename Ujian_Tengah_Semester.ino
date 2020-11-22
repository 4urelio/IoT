#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define BLYNK_PRINT Serial
#define DHTTYPE DHT11
#define DHTPIN 22
#define LDR 35

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

int tombol = V8;
int sliderSuhu = V5;
int sliderCahaya = V4;
float nilai = 0.009768;

WidgetLED ledSuhu = V7;
WidgetLED ledCahaya = V6;

char auth[] = "Ylcpp8rwY1yNU0z5B_fuI0hPaWishyLi";
char ssid[] = "";
char pass[] = "";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, IPAddress(192,168,18,13),8080);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //Serial.println("WiFi connected");
  //Serial.print("Connecting to ");
  //Serial.println(ssid);

  pinMode(21, OUTPUT);
  pinMode(19, OUTPUT);
  
  dht.begin();
  timer.setInterval(1000L, sendSensor);   
}

BLYNK_WRITE(V8){
  tombol = param.asInt();
  Serial.println(tombol);
}

BLYNK_WRITE(V5){
  sliderSuhu = param.asInt();
  Serial.println(sliderSuhu);
}

BLYNK_WRITE(V4){
  sliderCahaya = param.asInt();
  Serial.println(sliderCahaya);
}

void sendSensor()
{
  if(tombol == 1){
    float t = dht.readTemperature();
  
    if (isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    Serial.println(t);
    
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V3, t);

    if(sliderSuhu < t){
      digitalWrite(21, HIGH);
      Blynk.setProperty(V7, "color", "#FF0000");
      ledSuhu.on();
    } else {
      digitalWrite(21, LOW);
      Blynk.setProperty(V7, "color", "#008000");
      ledSuhu.on();
    }
    
    int sensorValue = analogRead(LDR);
    Serial.println(sensorValue);
    float hasil = (nilai * sensorValue) + 10;
    Blynk.virtualWrite(V1, hasil);
    Blynk.virtualWrite(V2, hasil);
    
    if(sliderCahaya < hasil){
      Blynk.setProperty(V6, "color", "#FF0000");
      digitalWrite(19, HIGH);
      ledCahaya.on();
    }
    else {
      digitalWrite(19, LOW);
      Blynk.setProperty(V6, "color", "#008000");
      ledCahaya.on();
    }
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}
