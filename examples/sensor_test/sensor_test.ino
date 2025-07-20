#include "FSS100.h"

FSS100 myFSS100(0x11);

void setup() {
  // put your setup code here, to run once:

  myFSS100.init();
}

void loop() {
  // put your main code here, to run repeatedly: 
  int16 theta = myFSS100.getTheta();
}
