/*
HANDCONTROL.C 


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
    
    SensorType[S2]=sensorTouch; //Initialize touch sensor
    bool isTouch = false; 

    SensorType[S1] = sensorColorNxtFULL; //Initialize colour sensor
    int colour = 0; 
    
    colour = SensorValue[S1]; 
    
    /*
    sendMessageWithParam(part_of_arm, direction_of_motion); 
    sendMessageWithParm(number_1,number_2,number_3);
    */ 
    
    //Output function DON'T FORGET 
    sendMessageWithParm(1, 2); //arm, drop
    while (SensorValue[S2] != 1){}
    stopArm(); //Make motorA and C = 0 BLUETOOTH  
    
    //Maybe change time/length based on object? 
    closeHand(true);
    
    //Look into merging 
    sendMessageWithParm(1, 1); //arm, lift
    sendMessageWithParm(2, 1); //wrist, cw
    
    wait1Msec(5000); 
    
    sendMessageWithParm(1, 2); //arm, drop
    while (SensorValue[S1] != -1){}
    stopArm(); 
      

    
    //Color snesor detects obj --> Via function, pass colour 
    //Output obj  
    //Drop hand until touch sensor is activated 
    //Stop moving 
    //Close fingers --> How long? Who knows  
    //Lift object --> Should be same as drop object 
    //Once at top, rotate wrist
    //Hangout 
    //Drop until colour sensor is activated 
    
    
		if (button == 3){
			idObject(); 
			closeHand(true); //Have some check for when to stop 
			
			sendMessage(1); //Arm up, wrist, arm down 
			
			closeHand(false); 
			
			displayString(1, "Done Routine"); 
		}
		
	
	}
}