const int redPin =  05;
const int yellowPin = 22;
const int greenPin = 16;

int redState = LOW;             
int yellowState = LOW;
int greenState = LOW;
long StartTime = 0;

long interval = 20000;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
 
  unsigned long CheckTime = millis();
  unsigned long elapsedTime = CheckTime - StartTime;


  if (elapsedTime > interval) {
    StartTime = CheckTime;
  }

  if (elapsedTime < 10000){
    redState = LOW;
    yellowState = LOW;
    greenState = HIGH;
  }

  if (elapsedTime > 10000&&elapsedTime < 15000){
    redState= LOW;
    yellowState = HIGH;
    greenState = LOW;
  }

  if (elapsedTime > 15000){
    redState = HIGH;
    yellowState = LOW;
    greenState = LOW;
  }
  digitalWrite(redPin,redState);
  digitalWrite(yellowPin,yellowState);
  digitalWrite(greenPin,greenState);
}
