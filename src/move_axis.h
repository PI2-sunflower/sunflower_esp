#include <Wire.h>

//void teste_ok_go_home(Stream * serial_arduino);
void go_home(Stream * serial_arduino, Stream * serial_ref);
void move_axis(String messageTemp, Stream * serial_arduino, Stream * serial_ref);



void go_home(Stream * serial_arduino, Stream * serial_ref){
  serial_ref->println("$H");
  serial_ref->println("$X");

  serial_arduino->println("$H");
  serial_arduino->println("$X");
}



void move_axis(String messageTemp, Stream * serial_arduino, Stream * serial_ref) {
  serial_ref->println(messageTemp);
  serial_arduino->println(messageTemp);

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
