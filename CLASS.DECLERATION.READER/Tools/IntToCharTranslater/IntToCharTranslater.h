
#ifndef INTTOCHARTRANSLATER_H
#define INTTOCHARTRANSLATER_H

#include <iostream>
#include <cstring>

class IntToCharTranslater
{
public:
  IntToCharTranslater();
  IntToCharTranslater(const IntToCharTranslater & orig);
  virtual ~IntToCharTranslater();
  char * Translate(int integer);
  int TranslateFromCharToInt(char * ch);
  int Power(int base,int power);
private:
  char BaseNumbers[10];
  char CharValue[3];
  int  IntegerValue;
  int  IntegerPower;
};

#endif /* INTTOCHARTRANSLATER_H */
