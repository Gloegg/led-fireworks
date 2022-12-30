
#include "Rocket.hpp"

#include <FastLED.h>
#include "Utils.hpp"

#define FADE_TO_BLACK_FACTOR 50
#define NUM_ROCKETS 3

CRGB leds[ NUM_LEDS ];

Rocket *rockets[ NUM_ROCKETS ];

void setup()
{
  FastLED.addLeds<NEOPIXEL, PIN_LED>( leds, NUM_LEDS );
  randomSeed( 0 );
  for ( int i = 0 ; i < NUM_ROCKETS; i++ )
  {
    rockets[ i ] = new Rocket();
  }
}

void loop()
{
  FastLED.show();
  FastLED.delay( 1000 / FRAMES_PER_SECOND );
  fadeToBlackBy( leds, NUM_LEDS, FADE_TO_BLACK_FACTOR );
  for ( int i = 0; i < NUM_ROCKETS; i++ )
  {
    if ( rockets[ i ]->isDone() )
    {
      delete rockets[ i ];
      rockets[ i ] = new Rocket();
    }
    rockets[ i ]->step();
    rockets[ i ]->draw( leds );
  }
}
