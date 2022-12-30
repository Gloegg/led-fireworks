#include "Rocket.hpp"
#include "Arduino.h"
#include "Utils.hpp"
#include <FastLED.h>

#define SPARKLES 33  // 0-99
#define EXPLOSION_RANGE 5
#define EXPLOSION_RADIUS 5.0

#define EXPLOSION_OFFSET 15 
#define EXPLOSION_RANGE 28

Rocket::Rocket()
{
  fX = random( 16 );
  fY = 0;
  fColorRed = random( 255 );
  fColorGreen = random( 255 );
  fColorBlue = random( 255 );
  fExplosionY = random( EXPLOSION_RANGE ) + EXPLOSION_OFFSET;  // Leave at least 5 pixels above explosion
  fExploding = false;
  fDone = false;
}

void Rocket::step()
{
  if ( !fExploding )
  {
    if ( fY < fExplosionY )
    {
      fY += 1;
    }
    else
    {
      fExploding = true;
    }
  }
  else
  {
    fDone = true;
  }
}

bool Rocket::isDone()
{
  return fDone;
}

float Rocket::getDistance( int x1, int x2, int y1, int y2 )
{
  int dx = x2 - x1;
  int dy = y2 - y1;
  if ( dx < 0 ) { dx *= -1; }
  if ( dy < 0 ) { dy *= -1; }
  return sqrt( dx * dx + dy * dy );
}


void Rocket::draw( CRGB *leds )
{
  if ( !fDone )
  {
    if ( !fExploding )
    {
      int idx = Utils::getIndexFromPos( fX, fY );
      if ( idx > 0 )
      {
        leds[ idx ].setRGB( fColorRed, fColorGreen, fColorBlue );
      }
    }
    else
    {
      for ( int x = -EXPLOSION_RANGE; x <= EXPLOSION_RANGE; x++ )
      {
        for ( int y = -EXPLOSION_RANGE; y <= EXPLOSION_RANGE; y++ )
        {
          if ( this->getDistance( fX, fX + x, fY, fY + y ) <= EXPLOSION_RADIUS && ( random( 100 ) < SPARKLES ) )
          {
            int idx = Utils::getIndexFromPos( fX + x, fY - y );
            if ( idx > 0 )
            {
              leds[ idx ].setRGB( fColorRed, fColorGreen, fColorBlue );
            }
          }
        }
      }
    }
  }
}
