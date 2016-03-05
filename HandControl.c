/*
This file contains the code that will move the fingers of the hand. 
There are three motors that will be used to move the fingers, with
the groupings being as follows: 
	Thumb - MotorA 
	Index and Middle Fingers - MotorB
	Ring and Pinky Fingers - MotorC 

This file will also gather sensor information, which will lead
to the fingers closing and grasping an object. 
*/


//Moves a general finger, look into replacing
//the three other functions with this one...
void moveFinger(int finger, bool close){
	time1[0] = 0; 

	if (close)
		motor[finger] = 50; 
	else
		motor[finger] = -50; 
	
	while (time1[0] < 2000){}
	motor[finger] = 0; 
}

void moveThumb(bool close){

	//Need to find optimal speed for closing and opening 
	time1[0] = 0; 

	if (close)
		motor[motorA] = 50; 
	else
		motor[motorA] = -50; 
	
	while (time1[0] < 2000){}
	motor[motorA] = 0; 

}

void moveIndex(bool close){

	time1[1] = 0; 

	if (close)
		motor[motorB] = 50; 
	else
		motor[motorB] = -50; 
	
	while (time1[1] < 2000){}
	motor[motorB] = 0; 

}

//Look into changing the function name 
void moveRingPinky(){

	time1[2] = 0; 

	if (close)
		motor[motorC] = 50; 
	else
		motor[motorC] = -50; 
	
	while (time1[2] < 2000){}
	motor[motorC] = 0; 

}

/*


*/
void openHand(bool close){

}

/*


*/
void closeHand(){

	//Example of closing all the fingers
	//motorA = 0, motorB = 1, motorC = 2
	moveFinger(0, true); 
	moveFinger(1, true); 
	moveFinger(2, true); 

}

task main (){


}