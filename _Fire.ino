
void Fire()
{
  for(uint8_t i = 0; i<numberOfFireFrames; i++)//for each frame
  {
    for(int j = 0; j< LEDCOUNT; j++)//for each eld in the frame
    {
        leds[j] = CRGB(fireFrames[i][j*3],fireFrames[i][j*3+1],fireFrames[i][j*3+2]);
    } 
    FastLED.show();
    delay(20);
    
  }
}
