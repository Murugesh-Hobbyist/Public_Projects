#include <Convert.h>

//Creation of class object
Convert convert;

void setup() {
  Serial.begin(115200);
  String bin = "11011001000000101000";
  //Conversion from binary to decimal
  Serial.print("11011001000000101000 converted to decimal: ");
  Serial.println(convert.binaryToDecimal(bin));
}

void loop() {
  //do nothing
}
