#include <Wire.h>

// UP AND DOWN VARIABLES
int pin_expand = 12, pin_retract = 14;
int pin_stop_retract = 32;
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
  //pinMode(pin_stop_up, INPUT);
  pinMode(pin_stop_retract, INPUT);

  // COMPRESSOR
  //ledcAttachPin(pin_expand, 2); //Atribuimos ao canal 2.
  //ledcSetup(2, 1000, 10); //Atribuimos ao canal 2 a frequencia de 1000Hz com resolucao de 10bits.
  digitalWrite(pin_expand, LOW);

  // VALVULA
  digitalWrite(pin_retract, LOW);

  //ledcWrite(2, 0);
}

void expand(Stream * serial_ref, PubSubClient * client) {
  serial_ref->println("** expand **");
  long lastMgsTime = millis();
  long expandStartTime = millis();

  //ledcWrite(2, vel_expand_retract);
  digitalWrite(pin_retract, LOW);
  digitalWrite(pin_expand,  HIGH);
  //delay(45000); //45

  while(true) {
    long currentTime = millis();
    if (currentTime - lastMgsTime > 5000) {
      lastMgsTime = currentTime;
      const char* busyString = "busy";
      serial_ref->print("status: ");
      serial_ref->println(busyString);
      client->publish("status", busyString);
    }
    if (currentTime - expandStartTime >= 45000) {
      break;
    }

    delay(50);
  }

  digitalWrite(pin_retract, LOW);
  digitalWrite(pin_expand,  LOW);
}

void retract(Stream * serial_ref, PubSubClient * client) {
  serial_ref->println("** retract **");
  long lastMgsTime = millis();
  long currentTime = millis();

  digitalWrite(pin_expand,  LOW);
  digitalWrite(pin_retract, HIGH);
  delay(300);
  
  while(digitalRead(pin_stop_retract) == LOW) {
    currentTime = millis();
    if (currentTime - lastMgsTime >= 5000) {
      lastMgsTime = currentTime;

      const char* busyString = "busy";
      serial_ref->print("status: ");
      serial_ref->println(busyString);
      client->publish("status", busyString);
    }
    delay(50);
  }
  delay(4000);
  digitalWrite(pin_expand,  LOW);
  digitalWrite(pin_retract, LOW);
}

void stop_expand_retract(Stream * serial_ref) {
  serial_ref->println("** stop up and down **");

  digitalWrite(pin_retract, LOW);
  digitalWrite(pin_expand,  LOW);
}
