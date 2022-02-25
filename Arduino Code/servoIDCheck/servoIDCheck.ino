#include <ax12.h>
#include <ax12.h>

//====================================================================================================
// Setup 
//====================================================================================================
void setup() {
  Serial.begin(38400);  // start off the serial port.  

  delay(250);
 
}

uint8_t ax_baud_divisor = 0;
//====================================================================================================
// Loop
//====================================================================================================
void loop() {
  unsigned long baud_rate = 2000000L/(ax_baud_divisor + 1);
  Serial.print("Try Baud: ");
  Serial.println(baud_rate);
  dxlInit(baud_rate);
  if (FindServos()) {
    Serial.println("Found a servo!");
    // wait until the user enters something to continue
    while (Serial.read() == -1) ;
    while (Serial.read() != -1) ;
  }
  ax_baud_divisor++; 
}

//=======================================================================================
bool FindServos(void) {

  bool found_servo = false;
  int w;
  Serial.println("Begin: ");
  for (int i = 0; i < 254; i++) {
    w = ax12GetRegister(i, AX_PRESENT_POSITION_L, 2 );
    if (w != (int)-1) {
      Serial.print(i, DEC);
      Serial.print(" - ");
      Serial.println(w, DEC);
      found_servo = true; 
    }    
    delay (10);
  }
  Serial.println("Done");
  return found_servo; 
}
