#define echoPinback 44 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinback 45 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPinright 42 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinright 43 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPinleft 40 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinleft 41 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPinfront 39 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinfront 38 //attach pin D3 Arduino to pin Trig of HC-SR04

const int buzzer = 9; //buzzer to arduino pin 9
int motorControllA = 3;
int motorControllB = 4;

int motorControllC = 5;
int motorControllD = 6;

int motorSpeed1 = 2;
int motorSpeed2 = 7;
int turn_delay = 10;

const int left_sensor_pin = A0;
const int right_sensor_pin = A1;

int left_sensor_state;
int right_sensor_state;

int spd = 10;
int prevspd = 10;

void setup() {
  Serial.begin(9600);
  pinMode(trigPinfront, OUTPUT);
  pinMode(echoPinfront, INPUT);
  pinMode(trigPinback, OUTPUT);
  pinMode(echoPinback, INPUT);
  pinMode(trigPinright, OUTPUT);
  pinMode(echoPinright, INPUT);
  pinMode(trigPinback, OUTPUT);
  pinMode(echoPinback, INPUT);
  pinMode(motorControllA, OUTPUT);
  pinMode(motorControllB, OUTPUT);
  pinMode(motorControllC, OUTPUT);
  pinMode(motorControllD, OUTPUT);
  pinMode(motorSpeed1, OUTPUT);
  pinMode(motorSpeed2, OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}

void loop() {
  if (Serial.available() > 0)
  {
    char data;
    data = Serial.read();
    Serial.write(Serial.read());
    switch (data)
    {
      case 'F': //FORWARD
        forward();
        break;
      case 'B': //REVERSE
        reverse();
        break;
      case 'L': //FORWARD LEFT
        left();
        break;
      case 'R': //FORWARD RIGHT
        right();
        break;
      case 'C':
        adaptivecruise();
        break;
      case 'S': //FORWARD LEFT
        halt();
        break;
      case '0': //FORWARD LEFT
        spd = 0;
        prevspd = spd;
        break;
      case '1': //FORWARD LEFT
        spd = 1;
        prevspd = spd;
        break;
      case '2': //FORWARD LEFT
        spd = 2;
        prevspd = spd;
        break;
      case '3': //FORWARD LEFT
        spd = 3;
        prevspd = spd;
        break;
      case '4': //FORWARD LEFT
        spd = 4;
        prevspd = spd;
        break;
      case '5': //FORWARD LEFT
        spd = 5;
        prevspd = spd;
        break;
      case '6': //FORWARD LEFT
        spd = 6;
        prevspd = spd;
        break;
      case '7': //FORWARD LEFT
        spd = 7;
        prevspd = spd;
        break;
      case '8': //FORWARD LEFT
        spd = 8;
        prevspd = spd;
        break;
      case '9': //FORWARD LEFT
        spd = 9;
        prevspd = spd;
        break;
      case 'M': //FORWARD LEFT
        spd = 10;
        prevspd = spd;
        break;
      default: //If bluetooth module receives any value not listed above, both motors turn off
        halt();
    }
  }
}
void right() {
  digitalWrite(motorControllA, LOW);
  digitalWrite(motorControllB, HIGH);
  analogWrite(motorSpeed1, 25.5 * spd);
  digitalWrite(motorControllC, HIGH);
  digitalWrite(motorControllD, LOW);
  analogWrite(motorSpeed2, 10 * spd);
}
void left() {
  digitalWrite(motorControllA, LOW);
  digitalWrite(motorControllB, HIGH);
  analogWrite(motorSpeed1, 10 * spd);
  digitalWrite(motorControllC, HIGH);
  digitalWrite(motorControllD, LOW);
  analogWrite(motorSpeed2, 25.5 * spd);

}
void forward() {
  digitalWrite(motorControllA, LOW);
  digitalWrite(motorControllB, HIGH);
  analogWrite(motorSpeed1, 25.5 * spd);

  digitalWrite(motorControllC, HIGH);
  digitalWrite(motorControllD, LOW);
  analogWrite(motorSpeed2, 25.5 * spd);
}
void reverse() {
  digitalWrite(motorControllA, HIGH);
  digitalWrite(motorControllB, LOW);
  analogWrite(motorSpeed1, 25.5 * spd);

  digitalWrite(motorControllC, LOW);
  digitalWrite(motorControllD, HIGH);
  analogWrite(motorSpeed2, 25.5 * spd);
}
void halt()
{
  digitalWrite(motorControllA, LOW);
  digitalWrite(motorControllB, LOW);
  analogWrite(motorSpeed1, 0);

  digitalWrite(motorControllC, LOW);
  digitalWrite(motorControllD, LOW);
  analogWrite(motorSpeed2, 0);
}
void beep() {
  while (!Serial.available()) {
    tone(buzzer, 2500); // Send 1KHz sound signal...
    delay(80);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(50);        // ...for 1sec
  }
}
void adaptivecruise() {
  while (!Serial.available()) {
    digitalWrite(trigPinfront, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinfront, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinfront, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPinfront, HIGH);
    int fdistance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Calculating the distance
    digitalWrite(trigPinback, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinback, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinback, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPinback, HIGH);
    int bdistance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    digitalWrite(trigPinleft, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinleft, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinleft, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPinleft, HIGH);
    int ldistance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    digitalWrite(trigPinright, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinright, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinright, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPinright, HIGH);
    int rdistance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    left_sensor_state = analogRead(left_sensor_pin);
    right_sensor_state = analogRead(right_sensor_pin);
    if (right_sensor_state < 500 && left_sensor_state > 500 && ldistance > 5) {
      left();
      delay(1000);
    }
    if (right_sensor_state > 500 && left_sensor_state < 500 && rdistance > 5) {
      right();
      delay(1000);
    }
    if (right_sensor_state > 500 && left_sensor_state > 500 && fdistance > 20) {
      spd = 10;
      forward();

    }
    if (right_sensor_state > 500 && left_sensor_state > 500 && fdistance < 20) {
      int  spd1 = spd * 25.5;
      while (fdistance < 20 ) {
        if (spd1 > 0)
          spd1--;
        digitalWrite(motorControllA, LOW);
        digitalWrite(motorControllB, HIGH);
        analogWrite(motorSpeed1, spd1);
        digitalWrite(motorControllC, HIGH);
        digitalWrite(motorControllD, LOW);
        analogWrite(motorSpeed2, spd1);
        digitalWrite(trigPinfront, LOW);
        delayMicroseconds(2);
        // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
        digitalWrite(trigPinfront, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPinfront, LOW);
        left_sensor_state = analogRead(left_sensor_pin);
        right_sensor_state = analogRead(right_sensor_pin);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPinfront, HIGH);
        fdistance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
        if (right_sensor_state < 500 && left_sensor_state > 500) {
          left();
          delay(1000);
        }
        if (right_sensor_state > 500 && left_sensor_state < 500) {
          right();
          delay(1000);
        }
      }
      forward();
    }
    if (rdistance < 8) {
      left();
      delay(2000);
      halt();
      beep();
    }
    if (ldistance < 8) {
      right();
      delay(2000);
      halt();
      beep();
    }
    if (bdistance < 8) {
      beep();
    }
  }
}
