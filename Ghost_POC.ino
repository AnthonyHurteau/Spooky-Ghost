int led[] = {
  11, 10, 9, 6
};
int ledCount = 4;

int pot = A0;
int potval = 0;

int potRange1 = 0;
int potRange2 = 255;
int potRange3 = 511;
int potRange4 = 766;
int potRange5 = 1023;

int timer = 250;
int faderTimer = 5;

void setup() {

  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(led[thisLed], OUTPUT);
  }
}

void loop() {

  potval = analogRead(pot);

  //#1 - All led chains OFF
  if (potval == potRange1) {
    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      digitalWrite(led[thisLed], LOW);
    }
  }

  //#2 All led chains ON
  if (potval > potRange1 && potval < potRange2) {

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      digitalWrite(led[thisLed], HIGH);
      potval = analogRead(pot);
      if (potval == potRange1 || potval >= potRange2) {
        for (int thisLed = 0; thisLed < ledCount; thisLed++) {
          digitalWrite(led[thisLed], LOW);
        }
      }
    }
  }

  //#3 All led chains blink at the same time
  if (potval >= potRange2 && potval < potRange3) {

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      digitalWrite(led[thisLed], HIGH);
    }

    delay(timer);

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      digitalWrite(led[thisLed], LOW);
    }

    delay(timer);
  }

  //#4 Blink one led chain at a time
  if (potval >= potRange3 && potval < potRange4) {

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      potval = analogRead(pot);
      if (potval < potRange3 || potval >= potRange4) {
        break;
      }
      digitalWrite(led[thisLed], HIGH);
      delay(timer);
      digitalWrite(led[thisLed], LOW);
      delay(timer);
    }
  }

  //#5 Open random led chain and close random led chain
  if (potval >= potRange4 && potval < potRange5) {
    int randNumber = random(ledCount);
    digitalWrite(led[randNumber], HIGH);
    delay(timer);
    randNumber = random(ledCount);
    digitalWrite(led[randNumber], LOW);
    delay(timer);
  }

  //#6 Fade in and open one led chain at a time into fade out and close
  //   one led chain at a time from first led chain to the last
  if (potval == potRange5) {

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      potval = analogRead(pot);
      if (potval != potRange5) {
        break;
      }
      for (int i = 0; i <= 255; i++) {

        analogWrite(led[thisLed], i);
        delay(faderTimer);

      }

      digitalWrite(led[thisLed], HIGH);
      delay(timer);
    }

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      potval = analogRead(pot);
      if (potval != potRange5) {
        break;
      }
      for (int i = 255; i >= 0; i--) {
        analogWrite(led[thisLed], i);
        delay(faderTimer);
      }

      digitalWrite(led[thisLed], LOW);
      delay(timer);
    }
  }
}


