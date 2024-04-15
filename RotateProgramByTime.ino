
/* NOT IN USE - Using Power cycle changes


#define FIRE_RUN_MINUTES 5
#define PLASMA_RUN_MINUTES 2
#define MINUTE_MULTIPLIER 60000


uint32_t fireRuntime = FIRE_RUN_MINUTES * MINUTE_MULTIPLIER; //5min
uint32_t plasmaRuntime = PLASMA_RUN_MINUTES * MINUTE_MULTIPLIER; //1 mimn
uint32_t programChangeTime = plasmaRuntime;

//Call This method
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

*/