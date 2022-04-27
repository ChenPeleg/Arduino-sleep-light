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
int analogLedPin9 = 9;
int analogLedPin10 = 10;
int analogLedPin11 = 11;
int ledPin = 13;                // LED
int pirPin = 2;                 // PIR Out pin
int pirStat = 0;                   // PIR status
int motionSensorValue;
int lightSensorValue;
unsigned long lastMovment = 0;
unsigned long lastLight;
bool dayLight = false;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Light sensor vlaue analog value is  900 or more in a dark room
  // and 500 or less in lighted room
  lightSensorValue = analogRead(A1);
  dayLight = lightSensorValue < 1000 ;

  Serial.println( lastMovment - lastLight  );


  pirStat = digitalRead(pirPin);
  motionSensorValue = analogRead(A0);
  //dayLight = false;
  if (motionSensorValue > 500 ) {
    if (!dayLight) {
      if (!isOn) {
        isOn = true;
        turnLightOn();
        
      } 
    }
    lastMovment = millis();
  }  else if (millis() - lastMovment   > 5000) {
    if (isOn) {
      turnLightOff();
      isOn = false;
    }
  }


}

void turnLightOn () {
  stepper(0, 5, 1);
  delay(1000);
}
void turnLightOff () {
  stepper(100,  5, -1);
}
void stepper (int baseValue,  int msSleep, double _step) {
  int luminnes = baseValue;
  for (int i = 0; i < 100; i++) {
    delay(msSleep);
    luminnes = luminnes + _step;
    analogWrite(analogLedPin9, luminnes );
    analogWrite(analogLedPin10, luminnes * 2 );
    analogWrite(analogLedPin11,  luminnes * 2 );
  }
}
