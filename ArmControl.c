/*
This file contains the code that controls the motion of the arm
and wrist. These functions are called via Bluetooth from the HandControl
program. 

Written By: Hernando Castano, Saienath Poopalarajah, Jio Wang

*/



/*
Activates the two motors at the elbow joint
in order to lift the arm.

Param lift boolean containing whether to raise or drop the elbow
*/
void liftArm (bool lift, int time){

	if (lift){
		motor[motorB] = 40;
		motor[motorC] = 40;

	}else {
		motor[motorB] = -40;
		motor[motorC] = -40;

	}

	wait1Msec(time);

	motor[motorB]=0;
	motor[motorC]=0;
}

/*
Rotates the wrist in a given direction through the
activation of motors for a specific amount of time.

Param cw Boolean contains the direction of rotation

*/

void rotateWrist(bool clockwise){

	nMotorEncoder[motorA] = 0;

	if (clockwise){
		motor[motorA] = 20;
		while (nMotorEncoder[motorA] <= 90){};

	}else{
		motor[motorA] = -20;
		while (nMotorEncoder[motorA] >= -90){};
	}

	motor[motorA] = 0;

}


void stopArm(){
	motor[motorA] = 0;
  motor[motorC] = 0;
}


bool messageAvailable(){
	if (message == 0){
		return false;
	}else{
		return true;
	}
}

int getMessage(){
		if (message != 0){
			int receivedMessage = message;
			ClearMessage();
			return receivedMessage;
		}else{
			return 0;

		}
}

task main(){

/* 	HOW THEY RECIEVE
 	message_first = messageParm[0];
	message_second = messageParm[1];
	message_third = messageParm[2];
*/
  ClearMessage();

	int firstMessage = 0, secondMessage = 0, thirdMessage = 0;

	while (true){

		if (messageAvailable() == true){

			firstMessage = messageParm[0];
      secondMessage = messageParm[1];
			thirdMessage = messageParm[2];

      if (firstMessage == 1){
        if (secondMessage == 1){
        	liftArm(true, thirdMessage);
        }else{
          if (secondMessage == 2){
            liftArm(false, thirdMessage);
          } //End of if
        } //End of else
      } //End of if
      else{

        if (firstMessage == 2){
          if (secondMessage == 1){
          	rotateWrist(true);
          }else{
            if (secondMessage == 2){
            	rotateWrist(false);
            }
          }
        }
      }
    }

    ClearMessage();
  }

  wait1Msec(100);

}
