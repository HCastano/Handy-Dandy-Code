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

void startRoutine(){
  sendMessageWithParm(1, 1); //arm, lift
  wait1Msec(3000);

  for (int i = 0; i < 2; i++){
  	sendMessageWithParm(2, 1); //wrist, cw
  	wait1Msec(2000);
  	sendMessageWithParm(2, 2); //wrist, ccw
  	wait1Msec(2000);
  }

}

void byeRoutine(){

  for (int i = 0; i < 3; i++){
		closeHand(true);
    closeHand(false);
  }

  sendMessageWithParm(1, 2); //arm, lift

}

void idObject(int colour, string &object){

  if (colour == 1){
  	object = "Black";
  }else if (colour == 2){
  	object = "Pepsi Can";
  }else if (colour == 3){

  }else if (colour == 4){
  	object = "Golf Ball";
  }else{
  	object = "White";
  }

}

void liftObject () {

  	sendMessageWithParm(1, 2);//arm, drop
    wait1Msec(2000);
 	 	closeHand(true);
    wait1Msec(2000);
  	sendMessageWithParm(1, 1); //arm, lift
    wait1Msec(2000);
  	sendMessageWithParm(2, 1); //wrist, cw
    wait1Msec(2000);
  	sendMessageWithParm(1, 2); //arm, drop
  	wait1Msec(2000);
  	closeHand(false);
  	wait1Msec(2000);
  	sendMessageWithParm(1,1);//arm, lift
  	wait1Msec(2000);
  	sendMessageWithParm(2,1);//wrist,cw
  	wait1Msec(2000);
}

void buttonPressAndRelease(){
	while (nNxtButtonPressed == -1){}
	while (nNxtButtonPressed != -1){}
}

void projectDemo(){

	sendMessageWithParm(3,0); //Bluetooth Message
	buttonPressAndRelease();

	string object = "";
	idObject(SensorValue[S2], object);
	displayString(0, "%s", object);
	buttonPressAndRelease();

	sendMessageWithParm(1, 1); //arm, lift
	wait1Msec(3000);
	sendMessageWithParm(1, 2); //arm, drop
	wait1Msec(3000);
	buttonPressAndRelease();

	sendMessageWithParm(2, 1); //wrist, cw
	wait1Msec(3000);
	sendMessageWithParm(2, 2); //wrist, cw
	wait1Msec(3000);
	buttonPressAndRelease();
	
	//ADD DEMO FOR FINGERS

}


task main (){

	wait1Msec(500);

	/*
	Transmits a sequence of integers ever 1/10th of a second.
	NOTE: A value of 0 CANNOT be sent via Bluetooth, as it
	indicates that no message is being sent.
	*/

	SensorType[S1] = sensorColorNxtFULL; //Initialize colour sensor
  int colour = 0;

  SensorType[S2]=sensorTouch; //Initialize touch sensor
  bool isTouch = false;

  startRoutine();

	while (true){


		while (nNxtButtonPressed == -1 && SensorValue[S2] == 0){}
		int button = nNxtButtonPressed;
		int sensorVal = SensorValue[S2];
		while (nNxtButtonPressed != -1 && SensorValue[S2] != 0){}

		if (sensorVal){
			displayString(0, "DEMOO");
			wait1Msec(3000);
			projectDemo();
		}

    colour = SensorValue[S1]; //Gets colour when button is pressed

    if (button == 3){
      string object = "";
      idObject(colour, object);
      displayString(0, "%s", object);
    	liftObject();
    }else if (button == 2){
    	//Second routine
    }else{
    	//Third routine
    }


    /*
    sendMessageWithParam(part_of_arm, direction_of_motion);
    sendMessageWithParm(number_1,number_2,number_3);
    */

	} //End of while-loop

  byeRoutine();

}