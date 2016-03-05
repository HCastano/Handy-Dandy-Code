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