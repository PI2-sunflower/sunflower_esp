void setup_magnetometer(Stream * serial_ref, Adafruit_BNO055 * bno) {
  if(!bno->begin()) {
    serial_ref->print("No BNO055 detected!");
    while(100);
  }
  delay(1000);
  bno->setExtCrystalUse(true);
}

String get_data(Stream * serial_ref, Adafruit_BNO055 * bno) {

  String magString = "";

  /* Get a new sensor event */
  sensors_event_t event;
  bno->getEvent(&event);

  magString += "X:"+String(event.orientation.x,4);
  magString += ",Y:"+String(event.orientation.y,4);
  magString += ",Z:"+String(event.orientation.z,4);

  // /* Display the floating point data */
  serial_ref->print("X: ");
  serial_ref->print(event.orientation.x, 4);
  serial_ref->print("\tY: ");
  serial_ref->print(event.orientation.y, 4);
  serial_ref->print("\tZ: ");
  serial_ref->print(event.orientation.z, 4);
  serial_ref->println("");

  // String orientationX = event.orientation.x;
  // String orientationY = event.orientation.y;
  // String orientationZ = event.orientation.z;
  //

  //serial_ref->println(magString);


  return magString;
}
