#ifndef ArduinoSerial_h
#define ArduinoSerial_h

class ArduinoSerialCommand {
  public:
    int c;
    int p1;
    int p2;
    int p3;
    int p4;
    int p5;
};

class ArduinoSerial
{
  public:
    ArduinoSerial(int baudRate);
    void initSerial();
    int getCommand(ArduinoSerialCommand * pc);

  private:
    int _baudRate;
    void parseSegment(ArduinoSerialCommand * pc, int state, char * data);
};

#endif
