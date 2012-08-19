#include "Arduino.h"
#include "ArduinoSerial.h"


ArduinoSerial::ArduinoSerial(int baudRate)
{
    _baudRate = baudRate;
}

void ArduinoSerial::initSerial()
{
    Serial.begin(_baudRate);
}

// the problem with the Serial.readBytesUntil method
// is that we don't know if the marker char has been read
// or if we failed in timeout
// one way to bypass this limitation is to have another marker
// in the protocol which would ensure that we read all the chracters
// of the message!
int ArduinoSerial::getCommand(ArduinoSerialCommand * pc)
{
    char buffer[132];

    // let's clear the structure which holds
    // the command
    pc->c = 0;
    pc->p1 = 0;
    pc->p2 = 0;
    pc->p3 = 0;
    pc->p4 = 0;
    pc->p5 = 0;
  
    int state = 0;

    int len = Serial.readBytesUntil('$', buffer, sizeof(buffer));

#ifdef DEBUG_SERIAL
    if (len > 0) {
        Serial.print("len: ");
        Serial.println(len,DEC);
    }
#endif

    if (len > 0) {
        buffer[len] = '\0';
        char temp[132];
        int iTemp = 0;
        temp[0] = '\0';
        for(int i = 0; i < sizeof(buffer) ; i++) {
            char c = buffer[i];
            if (c == '\0') {
                parseSegment(pc, state++, temp);
                state = -1;
                break;
            }   
            if (c == '#'){
                parseSegment(pc, state++, temp);
                state = 99;
                break;
            }
            if (c == ',') {
                parseSegment(pc, state++, temp);
                iTemp = 0;
            } else {
                temp[iTemp++] = c;
            }
            temp[iTemp] = '\0';
        }
    } else {
        return -1;
    }   
    if (state == 99) {
        return 0;
    } else {
        return -1;
    }
}

void ArduinoSerial::parseSegment(ArduinoSerialCommand * pc, int state, char * data) {
    if (strlen(data) <= 0) {
        return;
    }
    int value = atoi(data);
    switch(state) {
        case 0:
            pc->c = value;
            break;
        case 1:
            pc->p1 = value;
            break;
        case 2:
            pc->p2 = value;
            break;
        case 3:
            pc->p3 = value;
            break;
        case 4:
            pc->p4 = value;
            break;
        case 5:
            pc->p5 = value;
            break;
    }
}
