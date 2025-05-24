int LED1 = 3;
int LED2 = 2;
int LED3 = 4;
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
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
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

  if (message.equals("emotion:calm")) {
    playEmotion("calm");
  } else if (message.equals("emotion:angry")) {
    playEmotion("angry");
  } else if (message.equals("emotion:love")) {
    playEmotion("love");
  } else if (message.equals("OFF")) {
    digitalWrite(LED1, LOW);
  }
}

  delay(100);
}

void playEmotion(String emotion) {
  if (emotion == "calm") {
    blinkLed(LED1, 800);
  } else if (emotion == "angry") {
    blinkLed(LED1, 150);
  } else if (emotion == "love") {
    heartbeatPattern(LED1);
  }
}

void blinkLed(int pin, int delayTime) {
  for (int i = 0; i < 10; i++) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
  }
}

void heartbeatPattern(int pin) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pin, HIGH); delay(200);
    digitalWrite(pin, LOW);  delay(100);
    digitalWrite(pin, HIGH); delay(200);
    digitalWrite(pin, LOW);  delay(600);
  }
}