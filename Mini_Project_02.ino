#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 21
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int button1;
int tombol = 19;
int flag;

void setup() {
  pinMode(tombol, INPUT);
  pinMode (05 , OUTPUT);
  pinMode (16 , OUTPUT);
  pinMode (22 , OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  button1 = digitalRead(tombol);
  if(button1 == 1){
      flag = 1;
  }
  
  if(flag == 1){
    delay(3000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    //float f = dht.readTemperature(true);
    if (isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }
      
      Serial.print("Humidity: ");
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.println(" *C ");
      
      if (t <= 35) {
        Serial.println("Aman");
        digitalWrite(05, HIGH);
        digitalWrite(16, LOW);  
        digitalWrite(22, LOW);
      }
      if (t >=35.00 && t <= 50.00) {
        Serial.println("Siaga");
        digitalWrite(05, HIGH);
        digitalWrite(16, LOW);
        digitalWrite(22, HIGH);
      }
      if (t >= 50.00) {
        Serial.println("Darurat");
        digitalWrite(05, HIGH);
        digitalWrite(16, HIGH);
        digitalWrite(22, HIGH);
      }
  }
}
