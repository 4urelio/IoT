// This example uses an ESP32 Development Board
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <WiFi.h>
#include <MQTT.h>
#include <ESP32Servo.h>

#define LDRPIN 36

const char ssid[] = "Hello there";
const char pass[] = "Australia281198#";

WiFiClient net;
MQTTClient client;
Servo putarServo;

int servoPin = 23;
int posisiServo;
int sensorCahaya;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nconnecting...");
  while (!client.connect("ESP32", "9584fabd", "6a0b78d7ef566f59")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe("/test");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  
  if(topic == "/test"){
    if(payload == "1" && sensorCahaya >= 150){
      for (posisiServo = 0; posisiServo <= 180; posisiServo += 1){
        Serial.println("Servo did a full circle");
        putarServo.write(posisiServo);
      }
      client.publish("/test", "Servo has been rotated anti-clockwised");
      digitalWrite(02, HIGH);
      Serial.print("LED MENYALA");
    }
    else if(payload == "0" && sensorCahaya <= 2000){
      for (posisiServo = 180; posisiServo >= 0; posisiServo -= 1){
        Serial.println("Servo went back");
        putarServo.write(posisiServo);
      }
      client.publish("/test", "Servo has been rotated clockwised");
      digitalWrite(02, LOW);
      Serial.print("LED MATI");
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  putarServo.setPeriodHertz(50);
  putarServo.attach(servoPin, 500, 2400);
  pinMode(02, OUTPUT);
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  sensorCahaya = analogRead(LDRPIN);
  Serial.println(sensorCahaya);
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  
  if (!client.connected()) {
    connect();
  }
}
