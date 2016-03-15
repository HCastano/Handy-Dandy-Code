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

	//Why are the two encoder values different? 
	if (lift){
		motor[motorA] = 75;
		motor[motorC] = 75;
		while (nMotorEncoder[motorA]<720){};
	}else {
		//Check encoder value, something wrong 
		nMotorEncoder[motorA] = 720; 
		motor[motorA] = -75;
		motor[motorC] = -75;
		while (nMotorEncoder[motorA] > 0){}
		displayString(0, "Down"); 
	}
	
	time1[0] = 0; 
	while (time1[0] < 2000){} 
	
	motor[motorA]=0;
	motor[motorC]=0;
}


/*
Rotates the wrist in a given direction through the 
activation of motors for a specific amount of time. 

Param cw Boolean contains the direction of rotation

*/

void rotateWrist(bool clockwise){

	//Fix encoder
	nMotorEncoder[motorB] = 0; 
	
	if (clockwise){
		motor[motorB] = -25; 
		while (nMotorEncoder[motorB] >= -90){}	
	}else{
		motor[motorB] = 25; 
		while (nMotorEncoder[motorB] <= 90){}
	}
	
	time1[0] = 0; 
	while (time1[0] < 2000){}
	motor[motorB] = 0; 

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
		
	int my_message = 0; 

	while (true){

		if (messageAvailable() == true){

			my_message = getMessage(); //retrieve that message from memory.
			displayString(0,"%d",my_message);

			if (my_message == 1){
				liftArm(true); 
				rotateWrist(true); 
				liftArm(false); 
			}
			
		}

		wait1Msec(100); 

	}
}