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
	
	time[0] = 0; 

	if (lift)
		motor[motorA] = 75; 
		motor[motorB] = 75; 
	else
		motor[motorA] = -75; 
		motor[motorB] = -75; 
	

	while (time[0] < 2000){}
	motor[motorA] = 0; 
	motor[motorB] = 0; 
}

/*
Rotates the wrist in a given direction through the 
activation of motors for a specific amount of time. 

Param cw Boolean contains the direction of rotation

*/
void rotateWrist(bool clockwise){
	time[1] = 0; 

	if (clockwise)
		motor[motorC] = 35; 
	else
		motor[motorC] = -35; 

	while (time[1] < 1000){}
	motor[motorC] = 0; 

}

task main(){
	
}