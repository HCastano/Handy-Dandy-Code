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


//Moves a general finger
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
void closeHand(bool close){

	//Example of closing all the fingers
	//motorA = 0, motorB = 1, motorC = 2
	if (close){
		motor[0] = 50; 
		motor[1] = 50; 
	}else{
		motor[0] = -50; 
		motor[1] = -50; 
	} 
	
	time1[0] = 0; 
	while (time1[0] < 2000){}
	motor[0] = 0; 
	motor[1] = 0; 

}

void idObject(){

	displayString(3, "DON'T FORGET ME"); 

}

task main (){

	wait1Msec(500); 

	/*
	Transmits a sequence of integers ever 1/10th of a second. 
	NOTE: A value of 0 CANNOT be sent via Bluetooth, as it 
	indicates that no message is being sent. 
	*/

	
	/*
	sendMessage values: 
	1 - Function that lifts elbow, rotates wrist, then drops elblow 
	
	*/

	while (true){

		while (nNxtButtonPressed == -1){}
		int button = nNxtButtonPressed; 
		while (nNxtButtonPressed != -1){}

		if (button == 3){
			idObject(); 
			closeHand(true); //Have some check for when to stop 
			
			sendMessage(1); //Arm up, wrist, arm down 
			
			closeHand(false); 
			
			displayString(1, "Done Routine"); 
		}
		
	
	}
}