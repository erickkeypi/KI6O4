#ifndef _KI6O4_H_
#define _KI6O4_H_
#include "Arduino.h"

#ifdef _KI6O4_ESP8266
#define _KI6O4_BOARD_SET
#define IN2 14 //D5
#define IN3 2 //D4
#define IN4 13 //D7
#define IN5 0 //D3

#define OUT1 4 //D2
#define OUT2 15 //D8
#define OUT3 5 //D1

#define RE 16 //D0
#define DE 12 //D6
#define HC12_SET DE
#endif

#ifdef _KI6O4_ARDUINO_NANO
#define _KI6O4_BOARD_SET
#define IN1 6
#define IN2 A1
#define IN3 A2
#define IN4 5
#define IN5 A3
#define IN6 4

#define OUT1 A4
#define OUT2 3
#define OUT3 A5
#define OUT4 2

#define RE 13
#define DE 12
#define HC12_SET 7
#define SW2 11
#define STATUS A0
#endif

#ifdef _KI6O4_BOARD_SET

class KI6O4 {
private:

public:
  KI6O4(){}

  void begin(){
    pinMode(IN2,INPUT_PULLUP);
    pinMode(IN3,INPUT_PULLUP);
    pinMode(IN4,INPUT_PULLUP);
    pinMode(IN5,INPUT_PULLUP);

    pinMode(OUT1,OUTPUT);
    pinMode(OUT2,OUTPUT);
    pinMode(OUT3,OUTPUT);
    pinMode(RE,OUTPUT);
    pinMode(DE,OUTPUT);
    pinMode(HC12_SET,OUTPUT);

    #ifdef _KI6O4_ARDUINO_NANO

    pinMode(IN1,INPUT_PULLUP);
    pinMode(IN6,INPUT_PULLUP);
    pinMode(SW2,INPUT_PULLUP);

    pinMode(OUT4,OUTPUT);
    pinMode(STATUS,OUTPUT);
    #endif
  }

  bool read (byte _pin){
    #ifdef _KI6O4_ESP8266
    if(_pin == OUT1 || _pin == OUT2 ||_pin == OUT3){
      return digitalRead(_pin);
    }else{
      return !digitalRead(_pin);
    }
    #endif

    #ifdef _KI6O4_ARDUINO_NANO
    if(_pin == OUT1 || _pin == OUT2 || _pin == OUT3 || _pin == OUT4){
      return digitalRead(_pin);
    }else{
      return !digitalRead(_pin);
    }
    #endif
  }

  void write(byte _pin, bool _state){
    digitalWrite(_pin,_state);
  }

  void set(byte _pin){
    digitalWrite(_pin,HIGH);
  }

  void reset(byte _pin){
    digitalWrite(_pin,LOW);
  }

  void preTransmission(){
    digitalWrite(DE, 1);
    digitalWrite(RE, 1);
    delay(1);
  }

  void postTransmission(){
    Serial.flush();
    digitalWrite(DE,0);
    digitalWrite(RE,0);
  }

  void print(char *m){
    preTransmission();
    Serial.print(m);
    postTransmission();
  }

  void print(bool b){
    char buff[10];
    itoa(b,buff,10);
    print(buff);
  }
};

KI6O4 ki6o4 = KI6O4();
#endif
#endif
