/*

  PIR HCSR501

  modified on 5 Feb 2019
  by Saeed Hosseini @ ElectroPeak
  https://electropeak.com/learn/guides/
  Analog write:  A 2.5V analog signal is analogWrite(127)
  An average 5mm Red LED has a 2V forward voltage drop,

*/
int maxLuminnes = 100;
double luminnes = 0;
bool isOn = false;
int analogLedPin = 9;
int ledPin = 13;                // LED
int pirPin = 2;                 // PIR Out pin
int pirStat = 0;                   // PIR status
int sensorValue;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {




  pirStat = digitalRead(pirPin);
  sensorValue = analogRead(A0);
  if (sensorValue > 500) {
    if (!isOn) {
      isOn = true;
      turnLightOn();

    }
  }  else {
    if (isOn) {
      turnLightOff();
      isOn = false;
    }
  }

  Serial.println(sensorValue);

}
void turnLightOn () {
  stepper(0, 5, 1);
  delay(1500);
}
void turnLightOff () {
  stepper(100,  5, -1);
}
void stepper (int baseValue,  int msSleep, double _step) {
  int luminnes = baseValue;
  for (int i = 0; i < 100; i++) {
    delay(msSleep);
    luminnes = luminnes + _step;
    analogWrite(analogLedPin, luminnes );
  }
}
