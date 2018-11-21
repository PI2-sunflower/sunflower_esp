#include <Wire.h>

// UP AND DOWN VARIABLES
int pin_expand = 14, pin_retract = 12, pin_stop_up = 33, pin_stop_down = 32;
int vel_expand_retract = 1024;


/* MOVEMENT FUNCTIONS */
void setup_expand_retract_movement();
void expand(Stream * serial_ref);
void retract(Stream * serial_ref);
void stop_expand_retract(Stream * serial_ref);




// UP AND DOWN MOVEMENT FUNCTIONS
void setup_expand_retract_movement() {

  pinMode(pin_expand, OUTPUT);
  pinMode(pin_retract, OUTPUT);
  pinMode(pin_stop_up, INPUT);
  pinMode(pin_stop_down, INPUT);

  // COMPRESSOR
  //ledcAttachPin(pin_expand, 2); //Atribuimos ao canal 2.
  //ledcSetup(2, 1000, 10); //Atribuimos ao canal 2 a frequencia de 1000Hz com resolucao de 10bits.
  digitalWrite(pin_expand, LOW);

  // VALVULA
  digitalWrite(pin_retract, LOW);

  //ledcWrite(2, 0);
}

void expand(Stream * serial_ref) {
  serial_ref->println("** expand **");

  //ledcWrite(2, vel_expand_retract);
  digitalWrite(pin_retract, HIGH);
  digitalWrite(pin_expand,  HIGH);
  while(digitalRead(pin_stop_up) == LOW) {
    delay(10);
  }
  digitalWrite(pin_retract, LOW);
  digitalWrite(pin_expand,  LOW);
}

void retract(Stream * serial_ref) {
  serial_ref->println("** retract **");

  //ledcWrite(2, vel_expand_retract);
  digitalWrite(pin_expand,  LOW);
  digitalWrite(pin_retract, HIGH);
  while(digitalRead(pin_stop_down) == LOW) {
    delay(10);
  }
  digitalWrite(pin_expand,  LOW);
  digitalWrite(pin_retract, LOW);
}

void stop_expand_retract(Stream * serial_ref) {
  serial_ref->println("** stop up and down **");

  digitalWrite(pin_retract, LOW);
  digitalWrite(pin_expand,  LOW);
}
