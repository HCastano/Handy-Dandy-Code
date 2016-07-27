/*
This file contains the code that controls the motion of the arm
and wrist. These functions are called via Bluetooth from the HandControl
program. 

Written By: Hernando Castano, Saienath Poopalarajah, Jio Wang

*/



/*
Activates the two motors at the elbow joint in order to lift the arm.

Param: lift - boolean containing whether to raise or drop the arm
     time - integer with the length of time the action will be performed 

*/
void liftArm(bool lift, int time) {

  if (lift) {
    motor[motorB] = 40;
    motor[motorC] = 40;

  } else {
    motor[motorB] = -40;
    motor[motorC] = -40;

  }

  wait1Msec(time);
  motor[motorB] = 0;
  motor[motorC] = 0;
}

/*
Rotates the wrist 90 degrees in a specified direction. 

Param: clockwise - boolean that contains the direction of rotation

*/

void rotateWrist(bool clockwise) {

  nMotorEncoder[motorA] = 0;

  if (clockwise) {
    motor[motorA] = 20;
    while (nMotorEncoder[motorA] <= 90){};

  } else {
    motor[motorA] = -20;
    while (nMotorEncoder[motorA] >= -90){};
  }

  motor[motorA] = 0;
}


bool messageAvailable() {
  if (message == 0) {
    return false;
  } else {
    return true;
  }
}

int getMessage() {
  if (message != 0){
    int receivedMessage = message;
    ClearMessage();
    return receivedMessage;

  } else {
    return 0;
  }
}

task main() {

  ClearMessage();

  int firstMessage = 0, secondMessage = 0, thirdMessage = 0;

  // Loop is always checking if there are messages being sent from
  // the HandControl program. If so, it execute the appropriate action. 
  while (true) {
    if (messageAvailable() == true) {

    // The messages that were sent from HandControl are recieved here.
    // Each array entry represents the parameter in which the message
    // was sent. 
    firstMessage = messageParm[0];
    secondMessage = messageParm[1];
    thirdMessage = messageParm[2];

    if (firstMessage == 1) {
      if (secondMessage == 1) {
        liftArm(true, thirdMessage);
      } else {
          if (secondMessage == 2) {
            liftArm(false, thirdMessage);
          } // End of if
      } // End of else
    } else {
        if (firstMessage == 2) {
          if (secondMessage == 1) {
            rotateWrist(true);
          } else {
              if (secondMessage == 2) {
                rotateWrist(false);
              }
            }
          } // End of if 
        } // End of else
      }

    ClearMessage();

  } // End of loop

  wait1Msec(100);

}
