#include <Wire.h>

//void teste_ok_go_home(Stream * serial_arduino);
void go_home(Stream * serial_arduino, Stream * serial_ref);
void move_axis(String messageTemp, Stream * serial_arduino, Stream * serial_ref);
void clean_arduino_read_buffer(Stream * serial_arduino);


void clean_arduino_read_buffer(Stream * serial_arduino) {
  while(serial_arduino->available() > 0){
    serial_arduino->read();
  }
}

void go_home(Stream * serial_arduino, Stream * serial_ref){
  /*
    serial_arduino->println("$H");
    serial_arduino->println("$X");
  */

  // $H - GO HOME
  clean_arduino_read_buffer(serial_arduino);
  serial_ref->println("trying to: $H");
  serial_arduino->println("$H");
  delay(50);

  while (serial_arduino->readString() != "ok") {
    serial_ref->println("trying to: $H");
    serial_arduino->println("$H");
    delay(1000);
  }
  serial_ref->println("ok: $H");

  // $X - UNLOCK
  clean_arduino_read_buffer(serial_arduino);
  serial_ref->println("trying to: $X");
  serial_arduino->println("$X");
  delay(50);
  while (serial_arduino->readString() != "ok") {
    serial_ref->println("trying to: $X");
    serial_arduino->println("$X");
    delay(1000);
  }
  serial_ref->println("ok: $X");
}


void unlock(Stream * serial_arduino, Stream * serial_ref){

  // $X - UNLOCK
  delay(50);
  clean_arduino_read_buffer(serial_arduino);
  serial_ref->println("trying to: $X");
  serial_arduino->println("$X");
  delay(50);
  while (serial_arduino->readString() != "ok") {
    serial_ref->println("trying to: $X");
    serial_arduino->println("$X");
    delay(1000);
  }
  serial_ref->println("ok: $X");

}





void move_axis(String messageTemp, Stream * serial_arduino, Stream * serial_ref) {
  clean_arduino_read_buffer(serial_arduino);

  serial_ref->println(messageTemp);
  serial_arduino->println(messageTemp);

  delay(50);
  if (serial_arduino->read() == 'ok') {
    serial_ref->println('ok');
  }

}



//   void starGRBL(Stream * serial_arduino, Stream * serial_ref) {
//     serial_ref->println("Starting GRBL")
//
//     if (serial_arduino->available()>0){
//     	readGRBL = serial_arduino->read();
//
//     	if(readGRBL== "[‘$H’|’X’ to unlock]") {
//         serial_arduino->print("$X");
//    	    while (teste_ok()) {
//           serial_arduino->print("$X");
//         }
//       }
//     go_home(serial_arduino, serial_ref);
// }
//


// void teste_ok(Stream * serial_arduino){
//   testecon = 0;
//
//   while(true){
//     if (serial_arduino->available()>0){
//       readGRBL = Serial->read();
//       if(readGRBL == 'ok'){
//         return 0
//       }
//       testecon++;
//       if(testecon>=10){
//         return 1
//       }
//     } else {
//       // Restart system.
//       return 1
//     }
//   }
// }
