/*
ARMCONTROL.C

This file contains the code that will control the elbow joint, as
well as the wrist code.
*/

/*
Activates the two motors at the elbow joint
in order to lift the arm.

Param lift boolean containing whether to raise or drop the elbow
*/
void liftArm (bool lift){

	if (lift){
		motor[motorB] = -40;
		motor[motorC] = -40;

	}else {
		motor[motorB] = 40;
		motor[motorC] = 40;

	}

	wait1Msec(2000);

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
		while (nMotorEncoder[motorA] >= -90){};

	}else{
		motor[motorA] = -20;
		while (nMotorEncoder[motorA] <= 90){};
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

	int firstMessage = 0, secondMessage = 0;

	while (true){


		if (messageAvailable() == true){

			firstMessage = messageParm[0];
      secondMessage = messageParm[1];

      if (firstMessage == 1){
        if (secondMessage == 1){
        	liftArm(true);
        }else{
          if (secondMessage == 2){
            liftArm(false);
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
