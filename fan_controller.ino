// Fan Controller

// Constants
const int ledPin = 13;
const int outputPin = 3;

// Vars
volatile unsigned long timeold;
volatile int counter;
volatile unsigned int rpm;
byte pwm = 255;

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  analogWrite(outputPin, pwm);
  attachInterrupt(0,count,RISING);
  timeold = 0;
}

void loop() {
  // check for serial input
  while (Serial.available() > 0) {
    pwm = Serial.parseInt();
    analogWrite(outputPin, pwm);
  }
  
  check_rpm();
  Serial.print("PWM: ");
  Serial.print(pwm, DEC);
  Serial.print("\t");
  Serial.print("Count: ");
  Serial.print(counter, DEC);
  Serial.print("\t");
  Serial.print("RPM: ");
  Serial.println(rpm(), DEC);
  delay(100);
}

void count() {
  counter++;
}

void check_rpm() {
  if (counter >= 15 ) {
   rpm = 30*1000/(millis()-timeold)*counter; 
   timeold = millis();
   counter = 0;
  }
}
