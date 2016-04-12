#pragma config(Sensor, S4,     touchSensorL,    sensorEV3_Touch)
#pragma config(Sensor, S1,     touchSensorR,    sensorEV3_Touch)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)

void turnRight();
void turnLeft();
void backUp();
void travelLeft();
void travelRight();
void travelForward();
void sharpRight();
void sharpLeft();
task detectSensor();
task moveRandomly();
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task detectSensor() {
		int i = 0;
		bool back = false;
		while(true) {
				if (SensorValue[touchSensorR]) {
						while(i++ < 200) { //check for 300 ms (bar still isn't very sensitive)
							if(SensorValue[touchSensorL]) {
								back = true;
								i = 200;
								break;
							}
							wait1Msec(1);
						}
	  				stopTask(moveRandomly);
						stopAllMotors();
						if (back) {
							backUp();
						} else {
							turnLeft();
							travelLeft();
						}
						back = false;
						i = 0;
						startTask(moveRandomly);
				}
				if (SensorValue[touchSensorL]) {
						while (i++ < 200) {
							if (SensorValue[touchSensorR]){
								back = true;
								i = 200;
								break;
							}
							wait1Msec(1);
						}
						stopTask(moveRandomly);
						stopAllMotors();
						if (back) {
							backUp();
						} else {
							turnRight();
							travelRight();
						}
						back = false;
						i = 0;
						startTask(moveRandomly);
				}
				sleep(15);
		}
}

task moveRandomly
{

//getsensor value
//gettouch
//keep track of speeds and adjust slightly ever 15ms?

	int randomMove = random(5);
	while (true) {
  		if (randomMove == 0) {
				travelRight();
				randomMove = random(5);
	  	} else if (randomMove == 1) {
	  		travelLeft();
	  		randomMove = random(5);
		  } else if (randomMove == 2) {
		 		sharpRight();
		 		randomMove = random(1);
			} else if (randomMove == 3) {
				sharpLeft();
				randomMove = random(1);
			} else {//5
				//travelForward();
				randomMove = random(1);
			}
	 }
}

task main() {
	startTask(moveRandomly);
	startTask(detectSensor);
	while(true) {
		wait(300);
	}
}


/**
 * backs up for 2 seconds, then turns right at a random angle
 */
void turnRight() {
	displayCenteredBigTextLine(4, "Back");
	setLEDColor(ledOff);
	setMotor(motorC, -50);
	setMotor(motorB, -50);
	sleep(2000);
	sharpRight();
	/*setMotor(motorC, 10);
	setMotor(motorB, random(100));
	sleep(random(3000) + 500); //3 seconds good?
	*/
}

/**
 * backs up for 2 seconds, then turns left at a random angle
 */
void turnLeft() {
	displayCenteredBigTextLine(4, "Back");
	setLEDColor(ledOff);
	setMotor(motorB, -50);
	setMotor(motorC, -50);
	sleep(2000);
	sharpLeft();
	/*setMotor(motorB, 10);
	setMotor(motorC, random(80) + 20);
	sleep(random(3000) + 500);*/
}

/**
 * backs up, goes left or right randomely at a random angle
 */
void backUp() {
	playTone(400, 20);
	displayCenteredBigTextLine(4, "Back");
	setLEDColor(ledOff);
	setMotor(motorB, -50);
	setMotor(motorC, -50);
	sleep(2000);
	if (random(1)) //0 or 1, true or false... maybe?
	{
		sharpRight();
	}
	else {
		sharpLeft();
	}
	sleep(random(1500) + 1000);
}

void travelRight() {
	displayCenteredBigTextLine(4, "Right");
	setLEDColor(ledGreen);
	setMotor(motorB, 50);
	setMotor(motorC, 60);
	sleep(random(3000) + 500);
}

void travelLeft() {
	displayCenteredBigTextLine(4, "Left");
	setLEDColor(ledRed);
	setMotor(motorB, 60);
	setMotor(motorC, 50);
	sleep(random(3000) + 500);
}

void travelForward() {
	displayCenteredBigTextLine(4, "Straight");
	setLEDColor(ledOff);
	setMotor(motorB, 60);
	setMotor(motorC, 60);
	sleep(random(2000) + 500);
}

void sharpLeft() {
	displayCenteredBigTextLine(4, "Left");
	setLEDColor(ledRed);
	setMotor(motorB, 50);
	setMotor(motorC, 0);
	sleep(400);
}

void sharpRight() {
	displayCenteredBigTextLine(4, "Right");
	setLEDColor(ledGreen);
	setMotor(motorB, 0);
	setMotor(motorC, 50);
	sleep(400);
}
