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


/*


*/
void openHand(){
	
}

/*


*/
void closeHand(){

}

void moveThumb(bool close){

	//Need to find optimal speed for closing and opening 
	time[0] = 0; 

	if (close)
		motor[motorA] = 50; 
	else
		motor[motorA] = -50; 
	
	while (time[0] < 2000){}
	motor[motorA] = 0; 

}

void moveIndex(){

}

//Look into changing the function name 
void moveRingPinky(){

}

task main (){


}