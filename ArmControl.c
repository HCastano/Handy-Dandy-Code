/*
This file contains the code that will control the elbow joint, as
well as the wrist code. 
*/

/*
Activates the two motors at the elbow joint 
in order to lift the arm. 

Param lift Boolean containing whether to raise or drop the elbow
*/
void liftElbow(bool lift){
	
	time1[0] = 0; 

	if (lift){
		motor[motorA] = 75; 
		motor[motorB] = 75; 
	}else{
		motor[motorA] = -75; 
		motor[motorB] = -75; 
	}

	while (time1[0] < 2000){}
	motor[motorA] = 0; 
	motor[motorB] = 0; 
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

	motor[motorA] = 50;

	time1[0] = 0; 
	while (time1[0] < 1000); 

}

task main(){
	
	int my_message = 0; 

	while (true){

		if (messageAvailable() == true){
			activateMotor(getMessage());  
		}

		wait1Msec(100); 

	}
}