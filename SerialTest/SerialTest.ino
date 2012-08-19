
#include <ArduinoSerial.h>

const int C_PING = 1; // no params
const int C_PIN_MODE_OUTPUT = 10; // par1: pin number
const int C_PIN_MODE_INPUT = 11; // par1: pin number

const int C_DIGITAL_WRITE = 15; // par1: pin number, par2 : 0 or 1

// pins for the LEDs:
const int baudrate = 9600;

ArduinoSerial arduinoSerial(9600);

ArduinoSerialCommand C;

void setup() {
  arduinoSerial.initSerial();    
}

void loop()
{
  if (arduinoSerial.getCommand(&C) >= 0) {
    processCommand(&C);
  } 
 

}

void processCommand(ArduinoSerialCommand * pc) {
  
//  Serial.print("Cmde:");
//  Serial.println(pcmde->cmde, DEC);

    switch(pc->c) {
      case C_PING:
        ok();
       break;
       
       case C_PIN_MODE_OUTPUT:
       if (pc->p1 > 0) {
           pinMode(pc->p1, OUTPUT);
           ok();
       } else {
           err();
       }
       break;
       
       case C_PIN_MODE_INPUT:
       if (pc->p1 > 0) {
           pinMode(pc->p1, INPUT);
           ok();
       } else {
           err();
       }
       break;
       
       case C_DIGITAL_WRITE:
       if (pc->p1 > 0) {
           if (pc->p2 > 0) {
             digitalWrite(pc->p1, HIGH);
           } else {
             digitalWrite(pc->p1, LOW);
           }
           ok();
       } else {
           err();
       }
       break;
       
       
       default:
        msg("ERR:unknown");
       break;
      
    }
}

void ok() {
  Serial.println("OK");
}

void err() {
  Serial.println("ERR");
} 

void msg(char * msg) {
  Serial.println(msg);
}
