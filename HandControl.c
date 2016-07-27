/*
This file contains the code that controls the communication between
the two NXT bricks, executes routines (through the use of sensors),
and directly controls the motion of the fingers. 

Written By: Hernando Castano, Saienath Poopalarajah, Jio Wang

*/

void handShake();
void fistBump();
void moveFinger(int finger, bool close);
void closeHand(bool close, int power, int time);
void startRoutine();
void waveFingers();
void idObject(int colour, string &object);
void liftObject ();


/*
Either closes or opens any of the fingers of the hand. 

Param: finger - integer identifying the finger that is to be moved 
       close  - boolean indicating the direction of motion 

*/ 
void moveFinger(int finger, bool close) {
  
  time1[0] = 0;

  if (close) {
    motor[finger] = 50;
  } else {
    motor[finger] = -50;
  }

  while (time1[0] < 2000){}
  motor[finger] = 0;

}

/*
Either closes or opens any of the fingers of the hand. 

Param: close - boolean indicating the direction of motion 
       power - integer with the selected power level  
       time  - integer containing the duration of motion 

*/ 
void closeHand(bool close, int power, int time) {

  time1[0] = 0;

  if (close) {
    motor[motorA] = power;
    motor[motorB] = power;

  } else {
    motor[motorA] = -power;
    motor[motorB] = -power;

  }

  while (time1[0] < time){}

  motor[motorA] = 0;
  motor[motorB] = 0;

}

/*
Performs a routine that rotate the wrist in order to
replicate the "Queen's Wave". 

*/
void startRoutine() {

  wait1Msec(2000);

  //Waves twice 
  for (int i = 0; i < 2; i++) {
    sendMessageWithParm(2, 1); //wrist, cw
    wait1Msec(100);
    sendMessageWithParm(2, 2); //wrist, ccw
    wait1Msec(100);
  }
}

/*
Closes and opens the fingers of the hand in a waving gesture. 

*/
void waveFingers() {

  // Closes and opens three times
  for (int i = 0; i < 3; i++) {
    closeHand(true, 25, 500);
    wait1Msec(300);
    closeHand(false, 25, 500);
    wait1Msec(300);
  }

  wait1Msec(2000);

}

/*
A routine set up in order to simulate a handshake. 

The order of events are as follows: 
  Rotate Wrist
  Drop Arm
  Close Fingers 
  Go Up and Down (Shaking Hands)
  Open Fingers
  Lift Arm
  Rotate Wrist


*/
void handShake() {

  // Rotate Wrist
  sendMessageWithParm(2, 2);
  wait1Msec(1000);

  // Lift Arm
  sendMessageWithParm(1,2, 1200);
  wait1Msec(3000);

  // Close Fingers
  closeHand(true, 20, 400);

  // Shake Hand 
  for (int i = 0; i < 2; i++) {
    sendMessageWithParm(1, 1, 300);
    wait1Msec(300);

    sendMessageWithParm(1, 2, 300);
    wait1Msec(300);

  }

  // Open Fingers
  wait1Msec(1000);
  closeHand(false, 20, 400);
  wait1Msec(1000);

  // Lift Arm
  sendMessageWithParm(1, 1, 1200);
  wait1Msec(2000);

  // Rotate Wrist 
  sendMessageWithParm(2, 1);

}

/*
A routine that simulates a fist bump. 

*/ 
void fistBump() {

  // Drop Arm
  sendMessageWithParm(1, 2, 1000);
  wait1Msec(2000);

  // Close Fingers 
  closeHand(true, 30, 1000);
  wait1Msec(3000);

  // Open Fingers
  closeHand(false, 30, 1000);
  wait1Msec(1000);

  // Lift Arm 
  sendMessageWithParm(1, 1, 1000);
}

/*
Used to identify different object that the hand 
could pick up. 

Param: colour - integer containing the value of the actuate 
       object - string with the object that will be identified 
*/ 
void idObject(int colour, string &object) {

  if (colour == 1) {
    object = "Black";

  } else if (colour == 2) {
    object = "Pepsi Can";

  } else if (colour == 3) {
    object = "Tennis Ball";

  } else if (colour == 4) {
    object = "Golf Ball";

  } else {
      if (colour == 6){
      object = "White";
    }
  }
}

/*
Routine designed to grasp, lift, and put objects back down. 

The series of events are as follows: 
  Rotate Wrist
  Drop Arm
  Close Fingers (around object)
  Lift Arm
  Open Arm 
  Release Object 
  Lift Arm
  Rotate Wrist 

*/
void liftObject() {

  // Rotate Wrist 
  sendMessageWithParm(2, 2);

  // Drop Arm
  sendMessageWithParm(1, 2, 2000);//arm, drop
  wait1Msec(3000);

  // Close Hand - Grasp Object 
  closeHand(true, 45, 800);
  wait1Msec(1000);

  // Lift Arm
  sendMessageWithParm(1, 1, 2000);
  wait1Msec(5000);

  // Drop Arm
  sendMessageWithParm(1, 2, 2000);
  wait1Msec(2000);

  // Open Hand - Release Object 
  closeHand(false, 30, 1000);
  wait1Msec(2000);

  // Lift Arm
  sendMessageWithParm(1, 1, 2000);

  // Rotate Wrist 
  sendMessageWithParm(2, 1);

}

/*
The main function controls all the actions the arm is able to perform. 
It does this by taking input from various sensors, and calling 
the appropriate functions. 

Routines: 
All routines are started based on an assumed standard position of the arm. 
The stardard position is the arm lifted and the wrist neutral. 

Bluetooth: 
The HandControl program sent messages via Bluetooth the ArmControl program. 
This allowed for a way to control motors that were not directly attached 
to the brick without having to provide input in two different places. 

The sendMessageWithParam function was used to send messages, and it 
was used with the following convention: 

sendMessageWithParam(component, direction_of_motion)
sendMessageWithParam(component, direction_of_motion, time)

Where: 
The Arm had a component value of 1
The Wrist had a component value of 2  

direction_of_motion: 
  Arm:   1 = down 
         2 = up 
  Wrist: 1 = clockwise  
         2 = counterclockwise 

Time (for arm only): 
Corresponded to the length of time that the arm would be active in milliseconds

Ex. Lift Arm for 2 seconds: sendMessageWithParam(1, 1, 2000)
Ex. Rotate Wrist Clockwise: sendMessageWithParam(2, 1)

Note - A value of 0 cannot be sent via Bluetooth, as it indicates
the lack of a sent message. 

*/ 
task main () {

  wait1Msec(500);

  int button = 0, touch1Pressed = 0, touch2Pressed = 0,
  sonarDistance = 0, count = 0, colour = 0;

  //Initialize all the sensors 
  SensorType[S1] = sensorTouch;
  SensorType[S2] = sensorTouch;
  SensorType[S3] = sensorColorNxtFULL;
  SensorType[S4] = sensorSONAR;

  // Lifts arm into standard position and waves
  sendMessageWithParm(1, 1, 2000);
  startRoutine();

  while (true) {

    // Check whether anything is triggering an action
    while (nNxtButtonPressed == -1 && SensorValue[S1] == 0 
      && SensorValue[S2] == 0 && SensorValue[S4] > 10){}

    // Gathers all sensor data to proceed with action appropriately 
    button = nNxtButtonPressed;
    touch1Pressed = SensorValue[S1];
    touch2Pressed = SensorValue[S2];
    colour = SensorValue[S3]; 
    sonarDistance = SensorValue[S4];

    while (nNxtButtonPressed != -1 && SensorValue[S1] != 0 &&
      SensorValue[S2] != 0 && SensorValue[S4] < 20){}

    eraseDisplay();

    if (touch1Pressed) {
      startRoutine();
      displayString(4, "Start Routine");

    } else if (touch2Pressed) {
      waveFingers();
      displayString(4, "Good Bye");

    } else if(sonarDistance <= 10) {
      displayString(4, "Bump/Shake");

      // Allows for two gestures to be activated using the same sensor
      if (count % 2 == 0)
        handShake();
      else
        fistBump();

      count++;

    } else if (button == 1) {
      string object = ""; 
      idObject(colour, object); 
      displayString(4, "%s", object);
      liftObject(); 
    } else {
        if (button == 3) {
        displayString(4, "Exit");
        break;
      }
    }
  } // End of while-loop

  // Drop arm at the end of program
  sendMessageWithParm(1, 2, 2000);

}
