//For Teensy 4.0

#include <FastLED.h>

//Change Stuff
volatile uint16_t brightness = 255;
#define FIRE_RUN_MINUTES 5
#define PLASMA_RUN_MINUTES 2

//declarations
#define MINUTE_MULTIPLIER 60000
void Fire(); 
const int numberOfFireFrames = 350;
void Pink();
int mapLed(float s);
uint32_t Color(byte r, byte g, byte b);
void SelfCorrectMapping();
float SinCircleCentred(float x, float y, float size);
float SinCircle(float x, float y, float size);
float SinVerticle(float x, float y, float size);
float SinRotating(float x, float y, float size);

const int LEDCOUNT = 289; 
#define DATAPIN 3
CRGB leds[LEDCOUNT];

class LED
{
public:
      int idx;
      int x;
      int y;
      bool isCentre;
      LED(int _x, int _y, int _idx, bool _center)
      {
        x=_x;
        y=_y;
        idx=_idx;
        isCentre=_center;
      } 
 };
  
//each line is a strip 
LED pixels[] = 
{
LED(0,0,0,0), //level shifter led.
LED(14,0,1,0),LED(16,0,2,0),LED(18,0,3,0),LED(20,0,4,0),LED(22,0,5,0),LED(24,0,6,0),LED(26,0,7,0),LED(28,0,8,0),LED(30,0,9,0),LED(32,0,10,0),
LED(39,4,11,0),LED(37,4,12,0),LED(35,4,13,0),LED(33,4,14,0),LED(31,4,15,0),LED(29,4,16,0),LED(27,4,17,0),LED(25,4,18,0),LED(23,4,19,0),LED(21,4,20,0),LED(19,4,21,0),LED(17,4,22,0),LED(15,4,23,0),LED(13,4,24,0),LED(11,4,25,0),LED(9,4,26,0),
LED(5,8,27,0),LED(7,8,28,0),LED(9,8,29,0),LED(11,8,30,0),LED(13,8,31,0),LED(15,8,32,0),LED(17,8,33,1),LED(19,8,34,1),LED(21,8,35,1),LED(23,8,36,1),LED(25,8,37,1),LED(27,8,38,1),LED(29,8,39,1),LED(31,8,40,1),LED(33,8,41,1),LED(35,8,42,1),LED(37,8,43,0),LED(39,8,44,0),LED(41,8,45,0),LED(43,8,46,0),
LED(47,12,47,0),LED(45,12,48,0),LED(43,12,49,0),LED(41,12,50,0),LED(39,12,51,1),LED(37,12,52,1),LED(35,12,53,1),LED(33,12,54,1),LED(31,12,55,1),LED(29,12,56,1),LED(27,12,57,1),LED(25,12,58,1),LED(23,12,59,1),LED(21,12,60,1),LED(19,12,61,1),LED(17,12,62,1),LED(15,12,63,1),LED(13,12,64,1),LED(11,12,65,0),LED(9,12,66,0),LED(7,12,67,0),LED(5,12,68,0),
LED(4,16,69,0),LED(6,16,70,0),LED(8,16,71,0),LED(10,16,72,0),LED(12,16,73,1),LED(14,16,74,1),LED(16,16,75,1),LED(18,16,76,1),LED(20,16,77,1),LED(22,16,78,1),LED(24,16,79,1),LED(26,16,80,1),LED(28,16,81,1),LED(30,16,82,1),LED(32,16,83,1),LED(34,16,84,1),LED(36,16,85,1),LED(38,16,86,1),LED(40,16,87,1),LED(42,16,88,1),LED(44,16,89,0),LED(46,16,90,0),LED(48,16,91,0),LED(50,16,92,0),
LED(51,20,93,0),LED(49,20,94,0),LED(47,20,95,0),LED(45,20,96,0),LED(43,20,97,1),LED(41,20,98,1),LED(39,20,99,1),LED(37,20,100,1),LED(35,20,101,1),LED(33,20,102,1),LED(31,20,103,1),LED(29,20,104,1),LED(27,20,105,1),LED(25,20,106,1),LED(23,20,107,1),LED(21,20,108,1),LED(19,20,109,1),LED(17,20,110,1),LED(15,20,111,1),LED(13,20,112,1),LED(11,20,113,1),LED(9,20,114,1),LED(7,20,115,0),LED(5,20,116,0),LED(3,20,117,0),LED(1,20,118,0),
LED(2,24,119,0),LED(4,24,120,0),LED(6,24,121,0),LED(8,24,122,0),LED(10,24,123,1),LED(12,24,124,1),LED(14,24,125,1),LED(16,24,126,1),LED(18,24,127,1),LED(20,24,128,1),LED(22,24,129,1),LED(24,24,130,1),LED(26,24,131,1),LED(28,24,132,1),LED(30,24,133,1),LED(32,24,134,1),LED(34,24,135,1),LED(36,24,136,1),LED(38,24,137,1),LED(40,24,138,1),LED(42,24,139,1),LED(44,24,140,1),LED(46,24,141,0),LED(48,24,142,0),LED(50,24,143,0),LED(52,24,144,0),
LED(52,28,145,0),LED(50,28,146,0),LED(48,28,147,0),LED(46,28,148,0),LED(44,28,149,1),LED(42,28,150,1),LED(40,28,151,1),LED(38,28,152,1),LED(36,28,153,1),LED(34,28,154,1),LED(32,28,155,1),LED(30,28,156,1),LED(28,28,157,1),LED(26,28,158,1),LED(24,28,159,1),LED(22,28,160,1),LED(20,28,161,1),LED(18,28,162,1),LED(16,28,163,1),LED(14,28,164,1),LED(12,28,165,1),LED(10,28,166,1),LED(8,28,167,0),LED(6,28,168,0),LED(4,28,169,0),LED(2,28,170,0),
LED(1,32,171,0),LED(3,32,172,0),LED(5,32,173,0),LED(7,32,174,0),LED(9,32,175,1),LED(11,32,176,1),LED(13,32,177,1),LED(15,32,178,1),LED(17,32,179,1),LED(19,32,180,1),LED(21,32,181,1),LED(23,32,182,1),LED(25,32,183,1),LED(27,32,184,1),LED(29,32,185,1),LED(31,32,186,1),LED(33,32,187,1),LED(35,32,188,1),LED(37,32,189,1),LED(39,32,190,1),LED(41,32,191,1),LED(43,32,192,1),LED(45,32,193,0),LED(47,32,194,0),LED(49,32,195,0),LED(51,32,196,0),
LED(50,36,197,0),LED(48,36,198,0),LED(46,36,199,0),LED(44,36,200,0),LED(42,36,201,1),LED(40,36,202,1),LED(38,36,203,1),LED(36,36,204,1),LED(34,36,205,1),LED(32,36,206,1),LED(30,36,207,1),LED(28,36,208,1),LED(26,36,209,1),LED(24,36,210,1),LED(22,36,211,1),LED(20,36,212,1),LED(18,36,213,1),LED(16,36,214,1),LED(14,36,215,1),LED(12,36,216,1),LED(10,36,217,0),LED(8,36,218,0),LED(6,36,219,0),LED(4,36,220,0),
LED(5,40,221,0),LED(7,40,222,0),LED(9,40,223,0),LED(11,40,224,0),LED(13,40,225,1),LED(15,40,226,1),LED(17,40,227,1),LED(19,40,228,1),LED(21,40,229,1),LED(23,40,230,1),LED(25,40,231,1),LED(27,40,232,1),LED(29,40,233,1),LED(31,40,234,1),LED(33,40,235,1),LED(35,40,236,1),LED(37,40,237,1),LED(39,40,238,1),LED(41,40,239,0),LED(43,40,240,0),LED(45,40,241,0),LED(47,40,242,0),
LED(43,44,243,0),LED(41,44,244,0),LED(39,44,245,0),LED(37,44,246,0),LED(35,44,247,0),LED(33,44,248,1),LED(31,44,249,1),LED(29,44,250,1),LED(27,44,251,1),LED(25,44,252,1),LED(23,44,253,1),LED(21,44,254,1),LED(19,44,255,1),LED(17,44,256,0),LED(15,44,257,0),LED(13,44,258,0),LED(11,44,259,0),LED(9,44,260,0),LED(7,44,261,0),LED(5,44,262,0),
LED(9,48,263,0),LED(11,48,264,0),LED(13,48,265,0),LED(15,48,266,0),LED(17,48,267,0),LED(19,48,268,0),LED(21,48,269,0),LED(23,48,270,0),LED(25,48,271,0),LED(27,48,272,0),LED(29,48,273,0),LED(31,48,274,0),LED(33,48,275,0),LED(35,48,276,0),LED(37,48,277,0),LED(39,48,278,0),
LED(32,52,279,0),LED(30,52,280,0),LED(28,52,281,0),LED(26,52,282,0),LED(24,52,283,0),LED(22,52,284,0),LED(20,52,285,0),LED(18,52,286,0),LED(16,52,287,0),LED(14,52,288,0)
};

//Program management
enum PROGRAM {fire, pink, fire2, rainbow };
PROGRAM currentProgram = fire; 
uint32_t fireRuntime = FIRE_RUN_MINUTES * MINUTE_MULTIPLIER; //5min
uint32_t plasmaRuntime = PLASMA_RUN_MINUTES * MINUTE_MULTIPLIER; //1 mimn
uint32_t programChangeTime = plasmaRuntime;

//Plasma animation variables
float movement = 0;
float movementFactor = 0.01031; //move along by...advances plasma animation
float mapMin = -201;
float mapMax = 201;
float r,g,b,shade;
 
void setup()
{
  Serial.begin(115200);
  Serial.println("*** RESET ***");
 
  FastLED.addLeds<WS2812B, DATAPIN, GRB>(leds, LEDCOUNT);
  FastLED.setBrightness(brightness);

  movement = random(0,20)/0.7; //randomize start pattern for plasma
}
 
void loop()
{
  RotateProgram();

  switch(currentProgram)
  {
    case fire:
      Fire(); 
      break;
    case fire2:
      FireCentre(10); 
      break;
    case rainbow: 
      RainbowMorphing(7);
      break;
    case pink: 
      Pink(4);
      break;
  }

}

void RotateProgram()
 {
   if(programChangeTime < millis())
    {
      Serial.println("Rotate");
      switch(currentProgram)
      {
        case fire:
          currentProgram = pink;
          movement = random(0,20)/0.7;
          break;
        case pink: 
          currentProgram = fire2;
          break;
        case fire2: 
          currentProgram = rainbow;
          movement = random(0,20)/0.7;
          break;
        case rainbow: 
          currentProgram = fire;
          break;
      }
      Serial.println(currentProgram); //{fire, pink, fire2, rainbow };
      SetNextProgramChangeTime();
    }
 }

void SetNextProgramChangeTime()
{
   switch(currentProgram)
  {
    case fire:
    case fire2:
      SetProgramChangeTime(fireRuntime);
      break;
    case pink:
    case rainbow:
      SetProgramChangeTime(plasmaRuntime);
      break;
  } 
}

void SetProgramChangeTime(uint32_t runtimeMs)
{
  programChangeTime = millis() + (runtimeMs);
  Serial.print("programChangeTime="); Serial.println(programChangeTime);
}

void ClearAll()
{
  for(int i = 0; i<LEDCOUNT; i++) leds[i] = 0;
}
 