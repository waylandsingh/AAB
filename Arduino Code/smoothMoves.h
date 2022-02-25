

#define ROT_PERIOD 12000 //milliseconds per full rotation and return
#define TILT_PERIOD 900   //milliseconds per full upward tilt and return
#define INCREMENT 100 //this is the millisecond increment for smooth motion


#define HOME_ROT 0
#define HOME_TILT 1138

#include <ax12.h>               //include base library for DYNAMIXELs
#include <BioloidController.h>  //include bioloid libary for poses/movements

void SmoothMovement(){

//MoveHome();

unsigned long currentTimeMS = 0;
unsigned long lastTimeMS = 0;
int pan = HOME_ROT;
int tilt = HOME_TILT;

unsigned int  rotLoopTime;   //maintains time from 0 -> ROT PERIOD
int HALF_ROT = ROT_PERIOD/2;

unsigned int  tiltLoopTime;
int HALF_TILT = TILT_PERIOD/2;

int start = millis();


while(currentTimeMS<=(ROT_PERIOD))
{
currentTimeMS = millis() - start;

  if ((currentTimeMS-lastTimeMS)>=INCREMENT)
    {
    lastTimeMS = currentTimeMS;
    rotLoopTime = currentTimeMS%(ROT_PERIOD);
    tiltLoopTime = currentTimeMS%(TILT_PERIOD);
  
    if ((rotLoopTime)<(HALF_ROT))
        { 
       pan = map(rotLoopTime, 0,HALF_ROT,0, 4096); //map function is mort computationally efficient than triangle wave
      
        }
  
    if ( (rotLoopTime) >= (HALF_ROT) )
        {
         pan = map((rotLoopTime-HALF_ROT),0,HALF_ROT, 4096,0);
         }
    //delay(1);

    
    
    Serial.print(rotLoopTime);
   Serial.print("\t"); 
    Serial.print(pan);
    Serial.print(" pan");

     Serial.print(tiltLoopTime);
     Serial.print("\t");
     Serial.print(tilt);
    Serial.println(" tilt");
    }



}
Serial.print("The total time for a double rotation period is: ");
Serial.println(millis()-start);

}
