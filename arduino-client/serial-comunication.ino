int LED1 = 3;
int POTEN = A0;
int POTEN2 = A4;
int potValue;
int potValue2;
int dimmer;
int dimmer2;

int btn = 2;
int btnValue;



void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  pinMode(POTEN, INPUT);
  pinMode(POTEN2, INPUT);

  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(POTEN);
  potValue2 = analogRead(POTEN2);
  btnValue = digitalRead(btn);
  
  dimmer = map(potValue, 0, 1023, 0, 255);
  dimmer2 = map(potValue2, 0, 1023, 0, 255);
  String jsonString = "{\"potValue\":" + String(dimmer) +  ",\"btnValue\":" + String(btnValue) +   ",\"potValue2\":" + String(dimmer2) + "}";  // example of reading as json

  Serial.println(jsonString);  // send data through serial to any device or server who wants to read those data
  

  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    if (message.equals("ON")) {
      digitalWrite(LED1, HIGH);
    } else if (message.equals("OFF")) {
      digitalWrite(LED1, LOW);
    } else {
      // int sensorValue1 = message.toInt();
      // analogWrite(LED1, sensorValue1);
    }
  }

  delay(100);
}