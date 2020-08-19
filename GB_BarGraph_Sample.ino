/* This is a sample code to get a 28 segment bargraph working with any HT16K33 Breakout board.
   Author Mike Simone - August 2020
   The pinout for the BarGraph can be found online, the supplier is BarMeter.com
   There are 7 "row" outputs and 4 "column" references (7 blocks of 4 leds in total, Reference pins A0-A6 and C0-C3 of the HT16K33 Board)
   The HT16K33 board is powered by 5V and SDA / SCL pins go directly to pins A4 and A5 of the Arduino.
   SCL ----- A5
   SDA ----- A4
*/

#include <HT16K33.h>

HT16K33 bargraph = HT16K33();

/*
   Reindex Bargraph to be able to call segments from 0-27
   The BarGraph is indexed with a 4 x 7 matrix as per the datasheet from BarMeter.com
*/
uint16_t barGraph[28][2] = {
  {0, 0},
  {0, 1},
  {0, 2},
  {0, 3},
  {1, 0},
  {1, 1},
  {1, 2},
  {1, 3},
  {2, 0},
  {2, 1},
  {2, 2},
  {2, 3},
  {3, 0},
  {3, 1},
  {3, 2},
  {3, 3},
  {4, 0},
  {4, 1},
  {4, 2},
  {4, 3},
  {5, 0},
  {5, 1},
  {5, 2},
  {5, 3},
  {6, 0},
  {6, 1},
  {6, 2},
  {6, 3},
};

void setup() {
  /*
      Initiate the HT16K33
  */
  bargraph.init(0x70);
  delay(1000);
  bargraph.setBrightness(5);
}

void loop()
{
  /*
      Test some simple LED routines, first ramp to 28 then back down
      second start and 28 and drop down 8 segments and repeat
  */
  for (int segment = 0; segment < 28; segment++)
  {
    drawBarGraph(barGraph[segment][0], barGraph[segment][1], 1);
    delay(30);
  }

  for (int segment = 27; segment >= 0; segment--)
  {
    drawBarGraph(barGraph[segment][0], barGraph[segment][1], 0);
    delay(30);
  }
  bargraph.clear();
  delay(3000);
  for (int i = 0; i < 20; i++)
  {
    for (int segment = 0; segment < 28; segment++)
    {
      drawBarGraph(barGraph[segment][0], barGraph[segment][1], 1);
    }
    for (int segment = 27; segment >= 20; segment--)
    {
      drawBarGraph(barGraph[segment][0], barGraph[segment][1], 0);
      delay(10);
    }
  }
  bargraph.clear();
}

/*
   Draw function to write changes to the bargraph
*/
void drawBarGraph( uint8_t row, uint8_t col, uint8_t val )
{
  bargraph.setPixel(row, col, val);
  bargraph.write();
}
