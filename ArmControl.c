/*
This file contains the code that will control the elbow joint, as
well as the wrist code. 
*/

/*
Activates the two motors at the elbow joint 
in order to lift the arm. 

Param lift boolean containing whether to raise or drop the elbow
*/
void liftArm (bool lift){
  //Check the param being passed 
  
	nMotorEncoder[motorA]= 0;
	while (nNxtButtonPressed==-1){};

	if (nNxtButtonPressed==1){
		motor[motorA]=75;
		motor[motorC]=75;
		while (nMotorEncoder[motorA]<720){};
	}
	if (nNxtButtonPressed==2){
		motor[motorA]=-75;
		motor[motorC]=-75;
		while (nMotorEncoder[motorA]> 10){};
	}

	motor[motorA]=0;
	motor[motorC]=0;
}


/*
Rotates the wrist in a given direction through the 
activation of motors for a specific amount of time. 

Param cw Boolean contains the direction of rotation

*/
void rotateWrist(bool clockwise){
	time1[1] = 0; 

	if (clockwise)
		motor[motorC] = 35; 
	else
		motor[motorC] = -35; 

	while (time1[1] < 1000){}
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

void activateMotor(int num){

	motor[num - 1] = 20 * num;

	time1[0] = 0; 
	while (time1[0] < 1000); 

	motor[num - 1] = 0; 

}

task main(){
	
	int my_message = 0; 

	while (true){

		if (messageAvailable() == true){

			my_message = getMessage(); //retrieve that message from memory.
			displayString(0,"%d",my_message);

			activateMotor(my_message);  
		}

		wait1Msec(100); 

	}
}