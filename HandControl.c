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
void closeHand(bool close, int power, int time){

	if (close){
		motor[motorA] = power;
		motor[motorB] = power;
	}else{
		motor[motorA] = -power;
		motor[motorB] = -power;
	}

	time1[0] = 0;
	while (time1[0] < time){}
	motor[motorA] = 0;
	motor[motorB] = 0;

}

void startRoutine(){
  sendMessageWithParm(1, 1); //arm, lift
  wait1Msec(3000);

  for (int i = 0; i < 2; i++){
  	sendMessageWithParm(2, 1); //wrist, cw
  	wait1Msec(100);
  	sendMessageWithParm(2, 2); //wrist, ccw
  	wait1Msec(100);
  }
}

void byeRoutine(){

  for (int i = 0; i < 3; i++){
		closeHand(true, 0, 0);
    closeHand(false, 0, 0);
  }

  sendMessageWithParm(1, 2); //arm, drop

  wait1Msec(2000);
}

void idObject(int colour, string &object){

  if (colour == 1){
  	object = "Black";
  }else if (colour == 2){
  	object = "Pepsi Can";
  }else if (colour == 3){
		object = "Tennis Ball";
  }else if (colour == 4){
  	object = "Golf Ball";
  }else{
  	if (colour == 6){
  	object = "White";
  	}
  }
}

void liftObject () {

  	sendMessageWithParm(1, 2);//arm, drop
    wait1Msec(2000);
 	 	closeHand(true,0,0);
    wait1Msec(2000);
  	sendMessageWithParm(1, 1); //arm, lift
    wait1Msec(2000);
  	sendMessageWithParm(2, 1); //wrist, cw
    wait1Msec(1000);
  	sendMessageWithParm(1, 2); //arm, drop
  	wait1Msec(2000);
  	closeHand(false,0,0);
  	wait1Msec(2000);
  	sendMessageWithParm(1,1);//arm, lift
  	wait1Msec(2000);
  	sendMessageWithParm(2,1);//wrist,cw
  	wait1Msec(1000);
}

void buttonPressAndRelease(){
	while (nNxtButtonPressed == -1){}
	while (nNxtButtonPressed != -1){}
}

void projectDemo(){

	sendMessageWithParm(3,0); //Bluetooth Message
	buttonPressAndRelease();

	string object = "";
	idObject(SensorValue[S1], object);
	displayString(0, "%s", object);
	buttonPressAndRelease();

	sendMessageWithParm(1, 1); //arm, lift
	wait1Msec(3000);
	sendMessageWithParm(1, 2); //arm, drop
	wait1Msec(3000);
	buttonPressAndRelease();

	sendMessageWithParm(2, 1); //wrist, cw
	wait1Msec(1000);
	sendMessageWithParm(2, 2); //wrist, cw
	wait1Msec(1000);
	buttonPressAndRelease();

	//ADD DEMO FOR FINGERS
	moveFinger(0, 0);
	wait1Msec(2000);
	moveFinger(0, 1);
	wait1Msec(2000);
	moveFinger(1, 0);
	wait1Msec(2000);
	moveFinger(1, 1);
	wait1Msec(2000);
	closeHand(true,0,0);
	wait1Msec(2000);
	closeHand(false,0,0);


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
	buttonPressAndRelease();

	while (true){


		while (nNxtButtonPressed == -1 && SensorValue[S2] == 0){}
		int button = nNxtButtonPressed;
		int sensorVal = SensorValue[S2];
		while (nNxtButtonPressed != -1 && SensorValue[S2] != 0){}

		if (sensorVal){
			displayString(0, "DEMO");
			wait1Msec(1000);
			projectDemo();
			continue;
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



}
