#include <SoftwareSerial.h>

int RECV_PIN = 12;
int DCMOTOR_SLP = 3;

int DCMOTOR_AIN1 = 11;
int DCMOTOR_AIN2 = 10;

int PWM_VOLT = 171;

const long FORWARD = 49;
const long BACKWARD = 52;
const int LEFT = 51;
const int RIGHT = 50;
const long STOP = 48;
int STATE = 0;

SoftwareSerial hc06(2, 3);

void setup() {
  pinMode(DCMOTOR_SLP, OUTPUT);
  Serial.begin(9600);
  hc06.begin(9600);
}

void drive(int state) {
  switch(state) {
    case FORWARD:
      digitalWrite(DCMOTOR_AIN1, LOW);
      analogWrite(DCMOTOR_AIN2, PWM_VOLT);
      break;
    case BACKWARD:
      digitalWrite(DCMOTOR_AIN2, LOW);
      analogWrite(DCMOTOR_AIN1, PWM_VOLT);
      break;
    case STOP:
      digitalWrite(DCMOTOR_AIN1, LOW);
      digitalWrite(DCMOTOR_AIN2, LOW);
      digitalWrite(DCMOTOR_SLP, LOW);
      break;
    default:
      break;
  }
}
void loop() {
  digitalWrite(DCMOTOR_SLP, HIGH);
  int state;
  while(hc06.available())
  {
    state = hc06.read();
    Serial.println(state);
  }
  drive(state);
}
