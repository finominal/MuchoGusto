
//example of how to animate two sections. 
// pixel.isCentre tells us if the led falls in the centre section. 

void FireCentre(int size)
{
  for(int i = 0; i<numberOfFireFrames; i++)//for each frame
  {
    for(int j = 0; j<LEDCOUNT; j++)//for each pixel in the frame
    {

      //get pixel
      LED pixel = pixels[j]; 

      //SPLIT ANIMATIONS PER PIXEL
      if(!pixel.isCentre)
      { 
        //fire
        leds[j] = CRGB(fireFrames[i][j*3],fireFrames[i][j*3+1],fireFrames[i][j*3+2]);
      }
      else
      {
        //plasma
        shade = SinVerticle(pixel.x, pixel.y,size/4)
          //+ SinRotating(pixel.x, pixel.y,size)
          + SinCircle(pixel.x, pixel.y, size);
      
        leds[j] = CHSV(mapLED(shade), 255, brightness);

        //pale blue
        leds[j].g = leds[j].r/2; 
        leds[j].b = leds[j].r/4; //warm white
        leds[j].r = leds[j].r/2; 
      }

    } 
    
    FastLED.show();
    delay(15);
    
    movement+=movementFactor;  //moveplasma

  }
}