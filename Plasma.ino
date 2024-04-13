
void RainbowMorphing(float size)
{
  
  CRGB buffer;
  for(int i = 0; i<LEDCOUNT; i++)
  {
    LED pixel = pixels[i];

    shade = SinVerticle(pixel.x,pixel.y,size)
            + SinRotating(pixel.x,pixel.y,size)
            + SinCircle(pixel.x,pixel.y, size);
           
    leds[i] = CHSV(mapLED(shade), 255, brightness);
   
    int mg = 86 * abs(sin(movement/2));
    int mb = 86 * abs(cos(movement/4));
    //Serial.print(mg);Serial.print(" ");Serial.println(mb);
   
    //shift the blue
    buffer  = CHSV(mapLED(shade)-mg, 255, brightness);
    leds[i].b=buffer.b;
 
    //shift the grenn
    buffer = CHSV(mapLED(shade)+mb, 255, brightness);
    leds[i].g = buffer.g;
}
  FastLED.show();
  delay(20);
  movement+=movementFactor;
}

void Pink(float size)
{
  for(int i = 0; i<LEDCOUNT; i++)
  {
    LED pixel = pixels[i];

    shade = //SinVerticle(i,0,size)
            + SinRotating(pixel.x,pixel.y,size)
            + SinCircle(pixel.x,pixel.y, size);
 
    leds[i] = CRGB(mapLED(shade), 255, brightness);
    leds[i].g = leds[i].r/8;
    leds[i].b = leds[i].r/2;

   }
   
   movement+=movementFactor;
   FastLED.show();
   delay(20);
}
 
void RedGreen(float size)
{
  int s = size *.7;
  for(int i = 0; i<LEDCOUNT; i++)
  {
    LED pixel = pixels[i];
    shade = SinVerticle(pixel.x, pixel.y,s)
            + SinRotating(pixel.x, pixel.y,s)
            + SinCircle(pixel.x, pixel.y, s)
            ;
   
    leds[i] = CHSV(mapLED(shade), 255, brightness);
    leds[i].b = 0;
    leds[i].g += leds[i].r*abs(sin(movement/5));
 
  }
  movement+=movementFactor;
   FastLED.show();
   delay(20);
}
 
 
void RedBlue(float size)
{
  for(int i = 0; i<LEDCOUNT; i++)
  {
    LED pixel = pixels[i];
    shade = //SinVerticle(pixel.x, pixel.y,size)
            + SinRotating(pixel.x, pixel.y,size)
            + SinCircle(pixel.x, pixel.y, size)
            ;
 
    leds[i] = CHSV(mapLED(shade), 255, brightness);
    leds[i].g=0;
  }
  movement+=movementFactor;
  FastLED.show();
  delay(20);
}
 
void BlueGreen(float size)
{
  int s = size *.7;
  for(int i = 0; i<LEDCOUNT; i++)
  {
    LED pixel = pixels[i];
    shade = //SinVerticle(pixel.x, pixel.y,size)
            //+ SinRotating(pixel.x, pixel.y,size)
            + SinCircle(pixel.x, pixel.y, s)
            ;
   
    leds[i] = CHSV(mapLED(shade), 255, brightness);
    leds[i].r=0;
  
    
   }
   movement+=movementFactor;
  FastLED.show();
  delay(20);
}
 
void RedMorphing(float size)
{
  for(int i = 0; i<LEDCOUNT; i++)
  {
    LED pixel = pixels[i];
    shade = //SinVerticle(pixel.x, pixel.y,size)
            + SinRotating(pixel.x, pixel.y,size/2)
            + SinCircle(pixel.x, pixel.y, size)
            ;
 
      leds[i] = CHSV(mapLED(shade), 255, brightness);
      leds[i].g = 0;
      leds[i].b = leds[i].r*abs(sin(movement/2));
   }
   movement+=movementFactor;
  FastLED.show();
  delay(20);
}


void AquaCentred(float size)
{
  for(int i = 0; i<LEDCOUNT; i++)
  {
    LED pixel = pixels[i];
    shade = //SinVerticle(pixel.x, pixel.y,size)
              //+ SinRotating(pixel.x, pixel.y,size)
              + SinCircleCentred(pixel.x, pixel.y, size/2)
              ;
    leds[i] = CHSV(mapLED(shade), 255, brightness);
    leds[i].r = 0;
    leds[i].g = leds[i].b;
   
  }
  movement+=movementFactor/2;//bit faster5
  FastLED.show();
  delay(20);
}

void TestPlasma(float size)
{
  for(int i = 0; i<LEDCOUNT; i++)
  {
    LED pixel = pixels[i];
  shade = SinVerticle(pixel.x, pixel.y,size/4)
            + SinRotating(pixel.x, pixel.y,size/2)
            //+ SinCircleCentred(pixel.x, pixel.y, size/2)
            ;
   leds[i] = CHSV(mapLed(shade), 255, brightness);
   leds[i].r = 0;
   leds[i].g = leds[i].b;
   
  }
  movement+=movementFactor/2;
  FastLED.show();
  delay(20);
}

float SinVerticle(float x, float y, float size)
{
  return sin(x / size + movement);
}

//can we make this not zoom right out? 
float SinRotating(float x, float y, float size)
{
  return sin( (x * sin(movement/2 ) + y * cos(movement/5)) /size ) ;
}

float SinCircle(float x, float y, float size)
{
  float cx = LEDCOUNT * sin(movement/7);
  float cy = LEDCOUNT * cos(movement/2);
  float dist = sqrt(sq(cy-y) + sq(cx-x));
 
  return sin((dist/size ) + (movement) );
}

float SinCircleCentred(float x, float y, float size)
{
  float cx = (LEDCOUNT/2)-.5;
  float cy = 0;
  float dist = sqrt(sq(cy-y) + sq(cx-x));
 
  return sin((dist/size ) + (movement) );
}

void SelfCorrectMapping()
{
    //self correct mapping values to use maximum led resolution
    if(shade*100 < mapMin) mapMin = shade*100;
    if(shade*100 > mapMax) mapMax = shade*100;
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

int mapLED(float shade)
{
  return map(shade*100 ,mapMin, mapMax, 0, 255);
}
 