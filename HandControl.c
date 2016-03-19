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

void handShake();
void fistBump();
void moveFinger(int finger, bool close);
void closeHand(bool close, int power, int time);
void startRoutine();
void waveFingers();
void idObject(int colour, string &object);
void liftObject ();
void buttonPressAndRelease();

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

	//Get rid of close param by sending in negative
	//powers into the function

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
  sendMessageWithParm(1, 1, 2000); //arm, lift
  wait1Msec(3000);

  for (int i = 0; i < 2; i++){
  	sendMessageWithParm(2, 1); //wrist, cw
  	wait1Msec(100);
  	sendMessageWithParm(2, 2); //wrist, ccw
  	wait1Msec(100);
  }
}

void waveFingers(){

  for (int i = 0; i < 3; i++){
		closeHand(true, 25, 500);
		wait1Msec(500);
    closeHand(false, 25, 500);
    wait1Msec(500);
  }

  sendMessageWithParm(1, 2, 2000); //arm, drop

  wait1Msec(2000);
}

void handShake(){

		sendMessageWithParm(2, 2);
		wait1Msec(1000);

  	sendMessageWithParm(1,2, 1200);
  	wait1Msec(3000);

  	closeHand(true, 20, 400);

  	for (int i = 0; i < 2; i++){
  		sendMessageWithParm(1, 1, 300);
  		wait1Msec(300);
  		sendMessageWithParm(1, 2, 300);
  		wait1Msec(300);
  	}

  	wait1Msec(1000);
  	closeHand(false, 20, 400);
  	wait1Msec(1000);

  	sendMessageWithParm(1, 1, 1200);
  	wait1Msec(2000);

  	sendMessageWithParm(2, 1);

}

//How are we going to release it???
void fistBump(){
  sendMessageWithParm(1,2, 1000);
  wait1Msec(2000);
  closeHand(true, 30 , 1000);

  while (nNxtButtonPressed == -1){}
  while (nNxtButtonPressed != -1){}
  closeHand(false, 30, 1000);

  while (nNxtButtonPressed == -1){}
  while (nNxtButtonPressed != -1){}
  sendMessageWithParm(1,1, 1000);
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

		sendMessageWithParm(2, 1);
  	sendMessageWithParm(1, 2, 2000);//arm, drop
    wait1Msec(3000);
		while (nNxtButtonPressed == -1){}
		while (nNxtButtonPressed != -1){}

    closeHand(true, 45, 800);
    wait1Msec(1000);
    sendMessageWithParm(1, 1, 2000);
    wait1Msec(5000);
    sendMessageWithParm(1, 2, 2000);
    wait1Msec(2000);
    closeHand(false, 30, 1000);
    wait1Msec(2000);
    sendMessageWithParm(1, 1, 2000);
    sendMessageWithParm(2, 2);

}

void buttonPressAndRelease(){
	while (nNxtButtonPressed == -1){}
	while (nNxtButtonPressed != -1){}
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

	while (nNxtButtonPressed == -1){}
	while (nNxtButtonPressed != -1){}
	//fistBump();
	//handShake();
	//waveFingers();
	liftObject();
	while (nNxtButtonPressed == -1){}
	while (nNxtButtonPressed != -1){}

	while (true){

		while (nNxtButtonPressed == -1){}
		int button = nNxtButtonPressed;
		int sensorVal = SensorValue[S2];
		while (nNxtButtonPressed != -1){}

    colour = SensorValue[S1]; //Gets colour when button is pressed

    if (button == 3){
      string object = "";
      idObject(colour, object);
      displayString(4, "%s", object);
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
