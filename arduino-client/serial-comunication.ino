int LED1 = 3;
int LED_ROJO = 2;
int LED_VERDE = 9;
int LED_AZUL = 10;
int LED3 = 6;
int POTEN = A0;
int POTEN2 = A4;
int potValue;
int potValue2;
int dimmer;
int dimmer2;

int btn = 2;
int btnValue;
String currentEmotion = "";
String message = "";

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  pinMode(POTEN, INPUT);
  pinMode(POTEN2, INPUT);

  Serial.begin(9600);
  analogWrite(LED_ROJO, 0);
  analogWrite(LED_VERDE, 0);
  analogWrite(LED_AZUL, 0);
  analogWrite(LED3, 0);
}

void loop() {
  potValue = analogRead(POTEN);
  potValue2 = analogRead(POTEN2);
  btnValue = digitalRead(btn);

  dimmer = map(potValue, 0, 1023, 0, 255);
  dimmer2 = map(potValue2, 0, 1023, 0, 255);

  // CORREGIDO: comillas escapadas
  String jsonString = "{\"potValue\":" + String(dimmer) + ",\"btnValue\":" + String(btnValue) + ",\"potValue2\":" + String(dimmer2) + "}";

  Serial.println(jsonString);

  if (Serial.available()) {
  message = Serial.readStringUntil('\n');
  message.trim();
 
 if (message.startsWith("led3:")) {
      int value = message.substring(5).toInt();
      value = constrain(value, 0, 255); // Asegurar valor válido
      analogWrite(LED3,255 -  value);
    }


  if (message != currentEmotion) {
    currentEmotion = message;

    // Si el mensaje comienza con "emotion:"
    if (message.startsWith("emotion:")) {
      String emotion = message.substring(8); // Extrae solo la emoción
      playEmotion(emotion);
    }

    // Si el mensaje comienza con "color:"
    else if (message.startsWith("color:")) {
      String color = message.substring(6); // Extrae solo el color
      controlSemaforo(color);
    }
  }
}

}

// EMOCIONES
void playEmotion(String emotion) {
  digitalWrite(LED1, LOW);

  if (emotion == "calm") {
    digitalWrite(LED1, HIGH);
  } else if (emotion == "angry") {
    blinkLed(LED1, 150);
  } else if (emotion == "love") {
    heartbeatPattern(LED1);
  } else {
    digitalWrite(LED1, LOW);
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

// SEMÁFORO RGB
void controlSemaforo(String color) {
  analogWrite(LED_ROJO, 0);
  analogWrite(LED_VERDE, 0);
  analogWrite(LED_AZUL, 0);

  if (color == "rojo") {
    analogWrite(LED_ROJO, 255);
  } else if (color == "azul") {
    analogWrite(LED_AZUL, 255);
  } else if (color == "verde") {
    analogWrite(LED_VERDE, 255);
  }
}