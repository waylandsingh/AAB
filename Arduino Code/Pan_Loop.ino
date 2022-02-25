
/********************************************************
GAAB deployment software:

Uses arbotix-m board and 2 mx-64 servos to control oscillatory movement of whelen m9 beacon
Movement pattern is 2 independently rotating servos:
  1. which rotates in the horizontal plane from 0->360->0 repeatedly
  2. which rotates between 10 - 25deg above the horizontal (elevation angle)

***********************************************************************************/

#include <ax12.h>               //include base library for DYNAMIXELs
#include <BioloidController.h>  //include bioloid libary for poses/movements
#include "poses.h"              //home and center poses for the robot

BioloidController bioloid = BioloidController(1000000); //start the BIOLOID library at 1mbps. This will run the dxlInit() function internally, so we don't need to call it

const int SERVOCOUNT = 2;  //number of servos in this robot
int id;                    //temperary id for movement


const int readPin = 7;
int switchStatus = 0;

void setup()
{
  pinMode(USER_LED, OUTPUT); //user led as an output
  digitalWrite(USER_LED, HIGH); //set LED high to show that the test has started

//  Serial.begin(9600); //open serial port
  //Serial.println("######################################################");
 // Serial.println("Serial Comms Established. Starting Tests.");

 // dxlVoltageReport(SERVOCOUNT);  //serial report for the system voltage
  //dxlServoReport(SERVOCOUNT);    //Scan Servos, return position and error (if there are any)
 
  MoveHome();     //move servos to home position
 // MenuOptions();  //back to menu

}

void loop() {
  

switchStatus = digitalRead(readPin);
      if (switchStatus == HIGH)
      {
        SmoothMovement();
      }

// int inByte = Serial.read(); //read data from serial port for menu option
// disabled for field tests
  /*
  switch (inByte)
  {

    case '1':
      dxlServoReport(SERVOCOUNT);    //Scan Servos, return position and error
      MenuOptions();                 //show menu options
      break;

    case '2':
      switchStatus = digitalRead(readPin);
      if (switchStatus == HIGH)
      {
        SmoothMovement();
      }
      MenuOptions();                 //show menu options
      break;

    case '3':
      MoveHome();                    //move servos to home position
      MenuOptions();                 //show menu options
      break;

    case '4':
      dxlTorqueOffAll();             //turn the torque off to all servos
      MenuOptions();                 //show menu options
      break;

    case '5':
      //MoveCenter();                  //move all the servos to their centered position
      // MoveTest();                    //move each individual servo sequentially
      MenuOptions();                 //show menu options
      break;

    case '6':
      dxlVoltageReport(SERVOCOUNT);   //get and report average voltage
      MenuOptions();                 //show menu options
      break;

    case '7':
      Serial.println("Start LED Test");
      dxlLedTest(SERVOCOUNT, 3000);       //turn on/off each LED sequentially for 3000ms each
      Serial.println("End LED Test");
      MenuOptions();                 //show menu options
      break;

    case '8':
      dxlRegisterReport(SERVOCOUNT); //print out all register data to the serial port
      MenuOptions();                 //show menu options
      break;

    case '9':
      MenuOptions();
      MoveHome();
  }
  */
}


void MoveHome() {
  delay(100);                    // recommended pause
  bioloid.loadPose(Home);   // load the pose from FLASH, into the nextPose buffer
  bioloid.readPose();            // read in current servo positions to the curPose buffer
 // Serial.println("Moving servos to Home position");
  delay(1000);
  bioloid.interpolateSetup(2000); // setup for interpolation from current->next over 1/2 a second
  while (bioloid.interpolating > 0) { // do this while we have not reached our new pose
    bioloid.interpolateStep();     // move servos, if necessary.
    delay(3);
  }

}

void SmoothMovement() {

 // MoveHome();
  //All timing done with milliseconds...
  unsigned long totalLoopTime = 100000;//(ROT_PERIOD * 1.0 / 1000.0) * TILT_PERIOD * 50; //was *10!
  unsigned long currentTimeMS = 0;
  unsigned long lastTimeMS = 0;
  unsigned long timeSinceStart = 0;
  int pan = ROT_HOME;
  int tilt = TILT_HOME;
  unsigned int modifier; //for removing error buildup

  unsigned int  rotLoopTime;   //maintains time from 0 -> ROT PERIOD
  int HALF_ROT = ROT_PERIOD / 2; //less calculation needed below
  unsigned int  tiltLoopTime;   //tracks time from 0-> TILT PERIOD
  int HALF_TILT = TILT_PERIOD / 2;

  unsigned long start = millis();

  while ((timeSinceStart) < (totalLoopTime))
  {
    switchStatus = digitalRead(readPin);
    if (switchStatus == HIGH) 
    {
      currentTimeMS = millis();
      if ((currentTimeMS - lastTimeMS) >= INCREMENT)
      {

        timeSinceStart = currentTimeMS - start;
        modifier = 0;//timeSinceStart % INCREMENT;
        timeSinceStart = timeSinceStart - modifier;
        lastTimeMS = currentTimeMS;

        rotLoopTime = (timeSinceStart) % (ROT_PERIOD);
        tiltLoopTime = timeSinceStart % (TILT_PERIOD);

        //rotation calculations
        if ((rotLoopTime) < (HALF_ROT))
        {
          pan = map(rotLoopTime, 0, HALF_ROT, ROT_HOME, ROT_MAX); //map function is more efficient than triangle wave

        }

        if ( (rotLoopTime) >= (HALF_ROT) )
        {
          pan = map((rotLoopTime - HALF_ROT), 0, HALF_ROT, ROT_MAX, ROT_HOME);
        }

        //TILT calculation Block
        if ((tiltLoopTime) < (HALF_TILT))
        {
          tilt = map(tiltLoopTime, 0, HALF_TILT, TILT_HOME, TILT_MAX); //map function is more efficient than triangle wave
        }

        if ( (tiltLoopTime) >= (HALF_TILT) )
        {
          tilt = map((tiltLoopTime - HALF_TILT), 0, HALF_TILT, TILT_MAX, TILT_HOME);
        }

        dxlSetGoalPosition(1, pan);
        delay(3);
        dxlSetGoalPosition(2, tilt);
      }
    }
    else 
    {
      break;
    }
  }
 // Serial.println(millis() - start);
  start = millis();

  
 //temperatureSerialDisplay();//should display the temps of servo 1 and 2
}



void MenuOptions()
{
  Serial.println("###########################");
  Serial.println("Please enter option 1-8 to run individual tests again.");
  Serial.println("1) Servo Scanning Test");
  Serial.println("2) Move Servos to NEXT");
  Serial.println("3) Move Servos to Home");
  Serial.println("4) Relax Servos");
  Serial.println("5) Perform Movement Sign Test");
  Serial.println("6) Check System Voltage");
  Serial.println("7) Perform LED Test");
  Serial.println("8) Dump Servo Register Tables");
  Serial.println("9) Input a pan (0-4096) like this: \" 9 n: including the space' ");
  Serial.println("###########################");
}

void temperatureSerialDisplay()
{
  delay(20);
  int temp1=dxlGetTemperature(1);
  int temp2=dxlGetTemperature(2);

  Serial.print("the temps are:  ,");
  Serial.print(temp1);
  Serial.print(",");
  Serial.println(temp2);

  delay(10);
  
}


