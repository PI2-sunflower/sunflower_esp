#include <Wire.h>

// UP AND DOWN VARIABLES
int pin_up = 14, pin_down = 12;
int pin_up_stop = 35, pin_down_stop = 34;


/* MOVEMENT FUNCTIONS */
void setup_up_down_movement();
void go_up(Stream * serial_ref);
void go_down(Stream * serial_ref);
void stop_up_down(Stream * serial_ref);




// UP AND DOWN MOVEMENT FUNCTIONS
void setup_up_down_movement() {

  pinMode(pin_up, OUTPUT);
  pinMode(pin_down, OUTPUT);
  pinMode(pin_up_stop, INPUT);
  pinMode(pin_down_stop, INPUT);

  digitalWrite(pin_up, LOW);
  digitalWrite(pin_down, LOW);
}

void go_up(Stream * serial_ref) {
  serial_ref->println("** up **");

  digitalWrite(pin_down, LOW);
  digitalWrite(pin_up, HIGH);
  while(digitalRead(pin_up_stop) == HIGH){delay(50);}
  digitalWrite(pin_down, LOW);
  digitalWrite(pin_up, LOW);
}

void go_down(Stream * serial_ref) {
  serial_ref->println("** down **");

  digitalWrite(pin_up, LOW);
  digitalWrite(pin_down, HIGH);
  while(digitalRead(pin_down_stop) == HIGH){delay(50);}
  digitalWrite(pin_down, LOW);
  digitalWrite(pin_up, LOW);
}

void stop_up_down(Stream * serial_ref) {
  serial_ref->println("** stop up and down **");

  digitalWrite(pin_down, LOW);
  digitalWrite(pin_up, LOW);
}


// #include <Wire.h>
//
// // UP AND DOWN VARIABLES
// int pin_up_down_a = 26, pin_up_down_b = 27;
// int pin_ud_stop_up = 34, pin_ud_stop_down = 35;
// int vel_up_down = 1024;
//
//
// /* MOVEMENT FUNCTIONS */
// void setup_up_down_movement();
// void go_up(Stream * serial_ref);
// void go_down(Stream * serial_ref);
// void stop_up_down(Stream * serial_ref);
//
//
//
//
// // UP AND DOWN MOVEMENT FUNCTIONS
// void setup_up_down_movement() {
//
//   pinMode(pin_up_down_a, OUTPUT);
//   pinMode(pin_up_down_b, OUTPUT);
//   pinMode(pin_ud_stop_up, INPUT);
//   pinMode(pin_ud_stop_down, INPUT);
//
//   ledcAttachPin(pin_up_down_a, 0);//Atribuimos o pino 2 ao canal 0.
//   ledcSetup(0, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
//
//   ledcAttachPin(pin_up_down_b, 1);//Atribuimos o pino 2 ao canal 0.
//   ledcSetup(1, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
//
//   ledcWrite(0, 0);
//   ledcWrite(1, 0);
// }
//
// void go_up(Stream * serial_ref) {
//   serial_ref->println("** up **");
//
//   ledcWrite(1, 0);
//   ledcWrite(0, vel_up_down);
//   while(digitalRead(pin_ud_stop_up) == LOW) {
//     delay(10);
//   }
//   ledcWrite(0, 0);
//   ledcWrite(1, 0);
// }
//
// void go_down(Stream * serial_ref) {
//   serial_ref->println("** down **");
//
//   ledcWrite(0, 0);
//   ledcWrite(1, vel_up_down);
//   while(digitalRead(pin_ud_stop_down) == LOW) {
//     delay(10);
//   }
//   ledcWrite(0, 0);
//   ledcWrite(1, 0);
// }
//
// void stop_up_down(Stream * serial_ref) {
//   serial_ref->println("** stop up and down **");
//
//   ledcWrite(0, 0);
//   ledcWrite(1, 0);
// }
