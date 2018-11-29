#include <Wire.h>

// UP AND DOWN VARIABLES
int pin_up = 26, pin_down = 27;
int pin_up_stop = 35, pin_down_stop = 34;
int pin_reset = 33;


/* MOVEMENT FUNCTIONS */
void setup_up_down_movement();
void go_up(Stream * serial_ref, PubSubClient * client, Stream * serial_arduino);
void go_down(Stream * serial_ref, PubSubClient * client, Stream * serial_arduino);
void stop_up_down(Stream * serial_ref);

/* ARDUINO MOVEMENTS */



// UP AND DOWN MOVEMENT FUNCTIONS
void setup_up_down_movement() {

  pinMode(pin_up, OUTPUT);
  pinMode(pin_down, OUTPUT);
  pinMode(pin_reset, OUTPUT);
  pinMode(pin_up_stop, INPUT);
  pinMode(pin_down_stop, INPUT);

  digitalWrite(pin_up, LOW);
  digitalWrite(pin_down, LOW);
  digitalWrite(pin_reset, HIGH);
}

void go_up(Stream * serial_ref, PubSubClient * client, Stream * serial_arduino) {
  serial_ref->println("** up **");
  long lastMgsTime = millis();


  // while(digitalRead(pin_up_stop) == HIGH){
  //   delay(50);
  // }
  while(digitalRead(pin_up_stop) == HIGH) {
    digitalWrite(pin_down, LOW);
    digitalWrite(pin_up, HIGH);

    long currentTime = millis();
    if (currentTime - lastMgsTime > 5000) {
      lastMgsTime = currentTime;

      const char* busyString = "busy";
      serial_ref->print("status: ");
      serial_ref->println(busyString);
      client->publish("status", busyString);
    }
    delay(10);
  }
  digitalWrite(pin_down, LOW);
  digitalWrite(pin_up, LOW);
  delay(300);

  digitalWrite(pin_reset, LOW);
  delay(100);
  digitalWrite(pin_reset, HIGH);
  delay(1000);


  serial_arduino->println("$X");
  serial_ref->println("$X");
  delay(100);


  serial_arduino->println("$H");
  serial_ref->println("$H");
  delay(100);


  serial_arduino->println("G1 X-90 Y-5 Z-5 F600");
  serial_ref->println("G1 X-90 Y-5 Z-5 F600");
  delay(100);

}

void go_down(Stream * serial_ref, PubSubClient * client, Stream * serial_arduino) {
  serial_ref->println("** down **");

  serial_arduino->println("G1 X0 Y0 Z0 F1000");
  serial_ref->println("G1 X0 Y0 Z0 F1000");
  delay(15000);  // TODO:  15000

  // serial_arduino->println("G1 X0 Y0 Z0 F1000");
  // delay(100);

  long lastMgsTime = millis();
  long currentTime = millis();


  //delay(750);
  // while(digitalRead(pin_down_stop) == HIGH){
  //   delay(50);
  // }
  while(digitalRead(pin_down_stop) == HIGH) {
    digitalWrite(pin_up, LOW);
    digitalWrite(pin_down, HIGH);

    currentTime = millis();
    if (currentTime - lastMgsTime > 5000) {
      lastMgsTime = currentTime;

      const char* busyString = "busy";
      serial_ref->print("status: ");
      serial_ref->println(busyString);
      client->publish("status", busyString);
    }
    delay(50);
  }
  serial_ref->println("*** end down ***");

  digitalWrite(pin_down, LOW);
  digitalWrite(pin_up, LOW);
  delay(300);


  // digitalWrite(pin_reset, LOW);
  // delay(100);
  // digitalWrite(pin_reset, HIGH);
}

void stop_up_down(Stream * serial_ref) {
  serial_ref->println("** stop up and down **");

  digitalWrite(pin_down, LOW);
  digitalWrite(pin_up, LOW);
}
