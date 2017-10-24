int led[] = {
  3, 5, 6, 9, 10, 11
};
int ledCount = 6;

int ledFace = 2;

int pot = A0;
int potVal = 0;

int potRange0 = 0;
int potRange1 = 204;
int potRange2 = 408;
int potRange3 = 612;
int potRange4 = 816;
int potRange5 = 1015;

unsigned long previousMillis = 0;
const long timer1 = 250;
const long faderTimer1 = 5;
int ledState = LOW;

int timer = 250;
int faderTimer = 5;

void setup() {

  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(led[thisLed], OUTPUT);
  }
  pinMode(ledFace, OUTPUT);
  // Serial.begin(9600);
}

void loop() {

  unsigned long currentMillis = millis();
  potVal = analogRead(pot);
  //Serial.println(potVal);
  // delay(1);

  //#1 - Face leds behavior
  if (potVal == potRange0) {
    digitalWrite(ledFace, LOW);
  } else {
    digitalWrite(ledFace, HIGH);
  }

  //#2 - All led chains OFF
  if (potVal > potRange0 && potVal < potRange1) {
    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      digitalWrite(led[thisLed], LOW);
    }
  }

  //#3 All led chains ON
  if (potVal > potRange1 && potVal < potRange2) {

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      digitalWrite(led[thisLed], HIGH);
      potVal = analogRead(pot);
      if (potVal == potRange1 || potVal >= potRange2) {
        for (int thisLed = 0; thisLed < ledCount; thisLed++) {
          digitalWrite(led[thisLed], LOW);
        }
      }
    }
  }

  //#4 All led chains blink at the same time
  if (potVal >= potRange2 && potVal < potRange3) {

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      digitalWrite(led[thisLed], ledState);

      potVal = analogRead(pot);
      if (potVal == potRange1 || potVal >= potRange2) {
        for (int thisLed = 0; thisLed < ledCount; thisLed++) {
          digitalWrite(led[thisLed], LOW);
        }
      }

      if (currentMillis - previousMillis >= timer1) {
        previousMillis = currentMillis;

        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
      }
    }
  }

  //#5 Blink one led chain at a time
  /* if (potVal >= potRange3 && potVal < potRange4) {

     int thisLed = 0;

     if (currentMillis - previousMillis >= timer1) {
       previousMillis = currentMillis;

       if (thisLed < ledCount) {

         digitalWrite(led[thisLed], HIGH);
         thisLed = thisLed + 1;
       }

     }
    }
  */
  //#5 Blink one led chain at a time
  if (potVal >= potRange3 && potVal < potRange4) {

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      potVal = analogRead(pot);
      if (potVal < potRange3 || potVal >= potRange4) {
        break;
      }
      digitalWrite(led[thisLed], HIGH);
      delay(timer);
      potVal = analogRead(pot);
      if (potVal < potRange3 || potVal >= potRange4) {
        break;
      }
      digitalWrite(led[thisLed], LOW);
      delay(timer);
      potVal = analogRead(pot);
      if (potVal < potRange3 || potVal >= potRange4) {
        break;
      }
    }
  }


  //#6 Open random led chain and close random led chain
  if (potVal >= potRange4 && potVal < potRange5) {
    potVal = analogRead(pot);
    if (potVal < potRange4 || potVal >= potRange5) {
      for (int thisLed = 0; thisLed < ledCount; thisLed++) {
        digitalWrite(led[thisLed], LOW);
      }
    }
    int randNumber = random(ledCount);
    digitalWrite(led[randNumber], HIGH);
    potVal = analogRead(pot);
    if (potVal < potRange4 || potVal >= potRange5) {
      for (int thisLed = 0; thisLed < ledCount; thisLed++) {
        digitalWrite(led[thisLed], LOW);
      }
    }
    delay(timer);
    potVal = analogRead(pot);
    if (potVal < potRange4 || potVal >= potRange5) {
      for (int thisLed = 0; thisLed < ledCount; thisLed++) {
        digitalWrite(led[thisLed], LOW);
      }
    }
    randNumber = random(ledCount);
    digitalWrite(led[randNumber], LOW);
    potVal = analogRead(pot);
    if (potVal < potRange4 || potVal >= potRange5) {
      for (int thisLed = 0; thisLed < ledCount; thisLed++) {
        digitalWrite(led[thisLed], LOW);
      }
    }
    delay(timer);
    potVal = analogRead(pot);
    if (potVal < potRange4 || potVal >= potRange5) {
      for (int thisLed = 0; thisLed < ledCount; thisLed++) {
        digitalWrite(led[thisLed], LOW);
      }
    }
  }

  //#7 Fade in and open one led chain at a time into fade out and close
  //   one led chain at a time from first led chain to the last
  if (potVal >= potRange5) {

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      potVal = analogRead(pot);
      if (potVal < potRange5) {
        for (int thisLed = 0; thisLed < ledCount; thisLed++) {
          digitalWrite(led[thisLed], LOW);
        }
      }
      for (int i = 0; i <= 255; i++) {

        analogWrite(led[thisLed], i);
        delay(faderTimer);
        potVal = analogRead(pot);
        if (potVal < potRange5) {
          for (int thisLed = 0; thisLed < ledCount; thisLed++) {
            digitalWrite(led[thisLed], LOW);
          }
        }

      }

      digitalWrite(led[thisLed], HIGH);
      delay(timer);
      potVal = analogRead(pot);
      if (potVal < potRange5) {
        for (int thisLed = 0; thisLed < ledCount; thisLed++) {
          digitalWrite(led[thisLed], LOW);
        }
      }
    }

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      potVal = analogRead(pot);
      if (potVal < potRange5) {
        break;
      }
      for (int i = 255; i >= 0; i--) {
        analogWrite(led[thisLed], i);
        delay(faderTimer);
        potVal = analogRead(pot);
        if (potVal < potRange5) {
          for (int thisLed = 0; thisLed < ledCount; thisLed++) {
            digitalWrite(led[thisLed], LOW);
          }
        }
      }

      digitalWrite(led[thisLed], LOW);
      delay(timer);
      potVal = analogRead(pot);
      if (potVal < potRange5) {
        for (int thisLed = 0; thisLed < ledCount; thisLed++) {
          digitalWrite(led[thisLed], LOW);
        }
      }
    }
  }
}


