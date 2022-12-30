#ifndef Rocket_h
#define Rocket_h

#include "Utils.hpp"
#include <FastLED.h>

class Rocket
{
private:
  int fX;
  int fY;
  int fColorRed, fColorGreen, fColorBlue;
  int fExplosionY;
  bool fExploding;
  bool fDone;
  float getDistance(int x1, int x2, int y1, int y2);
public:
  Rocket();
  void step();
  void draw( CRGB *leds );
  bool isDone();
};

#endif