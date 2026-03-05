// LEFT DRIVER
#define L_RPWM 25
#define L_LPWM 26
#define L_REN 33
#define L_LEN 32

// RIGHT DRIVER
#define R_RPWM 27
#define R_LPWM 14
#define R_REN 12
#define R_LEN 13

void setup() {

pinMode(L_RPWM, OUTPUT);
pinMode(L_LPWM, OUTPUT);
pinMode(L_REN, OUTPUT);
pinMode(L_LEN, OUTPUT);

pinMode(R_RPWM, OUTPUT);
pinMode(R_LPWM, OUTPUT);
pinMode(R_REN, OUTPUT);
pinMode(R_LEN, OUTPUT);

digitalWrite(L_REN, HIGH);
digitalWrite(L_LEN, HIGH);

digitalWrite(R_REN, HIGH);
digitalWrite(R_LEN, HIGH);
}

void loop() {

forward();
delay(3000);

stopMotor();
delay(2000);

backward();
delay(3000);

stopMotor();
delay(2000);

left();
delay(3000);

stopMotor();
delay(2000);

right();
delay(3000);

stopMotor();
delay(2000);

}

// FORWARD
void forward(){
analogWrite(L_RPWM,200);
analogWrite(L_LPWM,0);

analogWrite(R_RPWM,200);
analogWrite(R_LPWM,0);
}

// BACKWARD
void backward(){
analogWrite(L_RPWM,0);
analogWrite(L_LPWM,200);

analogWrite(R_RPWM,0);
analogWrite(R_LPWM,200);
}

// LEFT
void left(){
analogWrite(L_RPWM,0);
analogWrite(L_LPWM,200);

analogWrite(R_RPWM,200);
analogWrite(R_LPWM,0);
}

// RIGHT
void right(){
analogWrite(L_RPWM,200);
analogWrite(L_LPWM,0);

analogWrite(R_RPWM,0);
analogWrite(R_LPWM,200);
}

// STOP
void stopMotor(){
analogWrite(L_RPWM,0);
analogWrite(L_LPWM,0);

analogWrite(R_RPWM,0);
analogWrite(R_LPWM,0);
}