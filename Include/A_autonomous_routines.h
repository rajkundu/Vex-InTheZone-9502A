/*--------------------------------------------------//--------------------------------------------------//

Team 9502A, Liberty High School VEX Robotics Team A
File: ../Include/A_autonomous_routines.h
Description: Contains Team A autonomous routines

//--------------------------------------------------//--------------------------------------------------*/

//Array of autonomous routine names
string routineNames[] =
{
	"   Do Nothing   ",
	"Straight & Stack",
	"  L-20  (Cones) ",
	"  R-20  (Cones) ",
	"  L-20 (Loader) ",
	"  R-20 (Loader) "
};

int numRoutines = sizeof(routineNames)/sizeof(routineNames[0]);

// ----------------------------------------------------------------- //

void resetRobot()
{
	//If the hoist is in the way of the mobile goal lift...
	if((SensorValue[hoistLimit] == 1)&&((SensorValue[liftBump] == 0)||(SensorValue[goalRetainerPot] > 0)))
	{
		while(SensorValue[hoistLimit] == 1)
		{
			//Raise hoist
			motor[leftHoist] = -64;
			motor[rightHoist] = 64;
		}
		wait1Msec(1000);
		//Keep hoist up
		motor[leftHoist] = -24;
		motor[rightHoist] = 24;
	}
	else
	{
		//Leave hoist as it is
		motor[leftHoist] = 0;
		motor[rightHoist] = 0;
	}

	//Release goal retainer
	while(SensorValue[goalRetainerPot] > 0)
	{
		motor[goalRetainer] = -127;
	}
	motor[goalRetainer] = 0;

	//Reset mobile goal lift
  while(SensorValue[liftBump] == 0)
  {
  	motor[leftLift] = 96;
		motor[rightLift] = -96;
  }
  motor[leftLift] = 0;
	motor[rightLift] = 0;

	//Reset hoist
  while(SensorValue[hoistLimit] == 0)
  {
  	motor[leftHoist] = 24;
		motor[rightHoist] = -24;
  }

  //Reset sensors to zero
  wait1Msec(1000);
  motor[leftHoist] = 0;
	motor[rightHoist] = 0;
  SensorValue[liftQuad] = 0;
  SensorValue[hoistQuad] = 0;
  SensorValue[gyro] = 0;
}

// ----------------------------------------------------------------- //

void drive(int y, int r)
{
	motor[leftDrive] = y + r;
	motor[rightDrive] = -y + r;
}
void stopDriving()
{
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}
void gyroTurn(int target, float k_p)
{
	int pidSpeed;
	int error = 0;
	string debugString;
	while(((-SensorValue[gyro] / 10.0) > (target + 5))||((-SensorValue[gyro] / 10.0) < (target - 5)))
	{
		//Set error
		error = target - (-SensorValue[gyro] / 10.0);
		//Set pidSpeed using error and constants
		pidSpeed = k_p * error;
		//Max speed 64
		pidSpeed = (pidSpeed > 64) ? 64 : pidSpeed;
		drive(0, pidSpeed);

		sprintf(debugString, "%f", -SensorValue[gyro] / 10.0);
		displayLCDCenteredString(0, debugString);
	}
	stopDriving();
}

task liftHoist()
{
	//Raise hoist
	while(SensorValue[hoistQuad] < 80)
	{
		motor[leftHoist] = -127;
		motor[rightHoist] = 127;
	}
	motor[leftHoist] = -16;
	motor[rightHoist] = 16;

	return;
}

task lowerGoalLift()
{
	//Lower goal lift
	while(SensorValue[liftQuad] > -210)
	{
		motor[leftLift] = -96;
		motor[rightLift] = 96;
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;

	return;
}

task dropCone()
{
	//Lower hoist
	while(SensorValue[hoistQuad] > 60)
	{
		motor[leftHoist] = 64;
		motor[rightHoist] = -64;
	}
	motor[leftHoist] = -16;
	motor[rightHoist] = 16;

	//Open claw/drop cone
	motor[claw] = +127;
	wait1Msec(500);

	//Raise hoist
	while(SensorValue[hoistQuad] < 90)
	{
		motor[leftHoist] = -127;
		motor[rightHoist] = 127;
	}
	motor[leftHoist] = -16;
	motor[rightHoist] = 16;
	motor[claw] = 0;

	return;
}

// ----------------------------------------------------------------- //
// ----------------------------------------------------------------- //
// ----------------------------------------------------------------- //

void straightAndStack()
{
	//Reset gyro
	SensorValue[gyro] = 0;

	startTask(liftHoist);
	while(SensorValue[hoistQuad] < 20)
	{
		EndTimeSlice();
	}
	wait1Msec(250);
	startTask(lowerGoalLift);

	//Drive straight
	drive(32, 0);
	wait1Msec(100);
	drive(64, 0);
	wait1Msec(100);
	drive(127, 0);
	wait1Msec(2200);
	stopDriving();

	//Lift goal
	while(SensorValue[liftQuad] < -15)
	{
		motor[leftLift] = 127;
		motor[rightLift] = -127;
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;
	//Stop driving
	stopDriving();

	//Activate goal retainer
	while(SensorValue[goalRetainerPot] < 1600)
	{
		motor[goalRetainer] = 127;
	}
	motor[goalRetainer] = 20;

	//Pause
	wait1Msec(250);

	//Drop cone
	startTask(dropCone);
}

// ----------------------------------------------------------------- //

void leftTwentyCones()
{
	//Reset gyro
	SensorValue[gyro] = 0;

	startTask(liftHoist);
	while(SensorValue[hoistQuad] < 20)
	{
		EndTimeSlice();
	}
	wait1Msec(250);
	startTask(lowerGoalLift);

	//Wait before driving forward
	wait1Msec(500);

	//Drive straight
	drive(32, 0);
	wait1Msec(100);
	drive(64, 0);
	wait1Msec(100);
	drive(127, 0);
	wait1Msec(1850);
	stopDriving();

	//Lift goal
	while(SensorValue[liftQuad] < -15)
	{
		motor[leftLift] = 127;
		motor[rightLift] = -127;
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;
	//Stop driving
	stopDriving();

	//Activate goal retainer
	while(SensorValue[goalRetainerPot] < 1600)
	{
		motor[goalRetainer] = 127;
	}
	motor[goalRetainer] = 20;

	//Pause
	wait1Msec(250);

	//Drive backward
	drive(-127, 0);

	startTask(dropCone);

	wait1Msec(1675);
	stopDriving();

	//Pause
	wait1Msec(250);

	//Turn around
	gyroTurn(135, 4.5);
	SensorValue[gyro] = 0;

	//Go back along 10-point bar
	drive(127, 0);
	wait1Msec(500);
	stopDriving();

	//Turn perpendicular to 20-point zone
	gyroTurn(90, 4.5);

	//Drive straight into 20-point zone
	drive(127, 0);
	wait1Msec(1000);
	stopDriving();

	//Release goal retainer
	while(SensorValue[goalRetainerPot] > 1600)
	{
		motor[goalRetainer] = -127;
	}
	motor[goalRetainer] = 0;

	//Lower goal lift & hoist
	while(SensorValue[liftQuad] > -210)
	{
		motor[leftLift] = -96;
		motor[rightLift] = 96;
		if(SensorValue[hoistQuad] > 90)
		{
			motor[leftHoist] = 16;
			motor[rightHoist] = -16;
		}
		else
		{
			motor[leftHoist] = -24;
			motor[rightHoist] = 24;
		}
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;

	//Drive backwards out of 20-point zone
	drive(-127, 0);
	wait1Msec(1000);
	stopDriving();
}

// ----------------------------------------------------------------- //

void rightTwentyCones()
{
	//Reset gyro
	SensorValue[gyro] = 0;

	startTask(liftHoist);
	while(SensorValue[hoistQuad] < 20)
	{
		EndTimeSlice();
	}
	wait1Msec(250);
	startTask(lowerGoalLift);

	//Wait before driving forward
	wait1Msec(500);

	//Drive straight
	drive(32, 0);
	wait1Msec(100);
	drive(64, 0);
	wait1Msec(100);
	drive(127, 0);
	wait1Msec(1850);
	stopDriving();

	//Lift goal
	while(SensorValue[liftQuad] < -15)
	{
		motor[leftLift] = 127;
		motor[rightLift] = -127;
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;
	//Stop driving
	stopDriving();

	//Activate goal retainer
	while(SensorValue[goalRetainerPot] < 1600)
	{
		motor[goalRetainer] = 127;
	}
	motor[goalRetainer] = 20;

	//Pause
	wait1Msec(250);

	//Drive backward
	drive(-127, 0);

	startTask(dropCone);

	wait1Msec(1675);
	stopDriving();

	//Pause
	wait1Msec(250);

	//Turn around
	gyroTurn(-135, 4.5);
	SensorValue[gyro] = 0;

	//Go back along 10-point bar
	drive(127, 0);
	wait1Msec(500);
	stopDriving();

	//Turn perpendicular to 20-point zone
	gyroTurn(-90, 4.5);

	//Drive straight into 20-point zone
	drive(127, 0);
	wait1Msec(1000);
	stopDriving();

	//Release goal retainer
	while(SensorValue[goalRetainerPot] > 1600)
	{
		motor[goalRetainer] = -127;
	}
	motor[goalRetainer] = 0;

	//Lower goal lift & hoist
	while(SensorValue[liftQuad] > -210)
	{
		motor[leftLift] = -96;
		motor[rightLift] = 96;
		if(SensorValue[hoistQuad] > 90)
		{
			motor[leftHoist] = 16;
			motor[rightHoist] = -16;
		}
		else
		{
			motor[leftHoist] = -24;
			motor[rightHoist] = 24;
		}
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;

	//Drive backwards out of 20-point zone
	drive(-127 , 0);
	wait1Msec(1000);
	stopDriving();
}

// ----------------------------------------------------------------- //

void leftTwentyLoader()
{
	//Reset gyro
	SensorValue[gyro] = 0;

	startTask(liftHoist);
	while(SensorValue[hoistQuad] < 20)
	{
		EndTimeSlice();
	}
	wait1Msec(250);
	startTask(lowerGoalLift);

	//Drive straight
	drive(32, 0);
	wait1Msec(100);
	drive(64, 0);
	wait1Msec(100);
	drive(127, 0);
	wait1Msec(1700);
	stopDriving();

	//Lift goal
	while(SensorValue[liftQuad] < -15)
	{
		motor[leftLift] = 127;
		motor[rightLift] = -127;
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;
	//Stop driving
	stopDriving();

	//Activate goal retainer
	while(SensorValue[goalRetainerPot] < 1600)
	{
		motor[goalRetainer] = 127;
	}
	motor[goalRetainer] = 20;

	//Pause
	wait1Msec(250);

	//Drive backward
	drive(-127, 0);

	startTask(dropCone);

	wait1Msec(1750);
	stopDriving();

	//Pause
	wait1Msec(250);

	//Turn around
	gyroTurn(150, 4.5);
	SensorValue[gyro] = 0;

	//Go back along 10-point bar
	drive(127, 0);
	wait1Msec(400);
	stopDriving();

	//Turn perpendicular to 20-point zone
	gyroTurn(90, 4.5);

	//Drive straight into 20-point zone
	drive(127, 0);
	wait1Msec(1000);
	stopDriving();

	//Release goal retainer
	while(SensorValue[goalRetainerPot] > 1600)
	{
		motor[goalRetainer] = -127;
	}
	motor[goalRetainer] = 0;

	//Lower goal lift & hoist
	while(SensorValue[liftQuad] > -210)
	{
		motor[leftLift] = -96;
		motor[rightLift] = 96;
		if(SensorValue[hoistQuad] > 90)
		{
			motor[leftHoist] = 16;
			motor[rightHoist] = -16;
		}
		else
		{
			motor[leftHoist] = -16;
			motor[rightHoist] = 16;
		}
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;

	//Drive backwards out of 20-point zone
	drive(-127, 0);
	wait1Msec(1000);
	stopDriving();
}

// ----------------------------------------------------------------- //

void rightTwentyLoader()
{
	//Reset gyro
	SensorValue[gyro] = 0;

	startTask(liftHoist);
	while(SensorValue[hoistQuad] < 20)
	{
		EndTimeSlice();
	}
	wait1Msec(250);
	startTask(lowerGoalLift);

	//Drive straight
	drive(32, 0);
	wait1Msec(100);
	drive(64, 0);
	wait1Msec(100);
	drive(127, 0);
	wait1Msec(1700);
	stopDriving();

	//Lift goal
	while(SensorValue[liftQuad] < -15)
	{
		motor[leftLift] = 127;
		motor[rightLift] = -127;
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;
	//Stop driving
	stopDriving();

	//Activate goal retainer
	while(SensorValue[goalRetainerPot] < 1600)
	{
		motor[goalRetainer] = 127;
	}
	motor[goalRetainer] = 20;

	//Pause
	wait1Msec(250);

	//Drive backward
	drive(-127, 0);

	startTask(dropCone);

	wait1Msec(1750);
	stopDriving();

	//Pause
	wait1Msec(250);

	//Turn around
	gyroTurn(-150, 4.5);
	SensorValue[gyro] = 0;

	//Go back along 10-point bar
	drive(127, 0);
	wait1Msec(400);
	stopDriving();

	//Turn perpendicular to 20-point zone
	gyroTurn(-90, 4.5);

	//Drive straight into 20-point zone
	drive(127, 0);
	wait1Msec(1000);
	stopDriving();

	//Release goal retainer
	while(SensorValue[goalRetainerPot] > 1600)
	{
		motor[goalRetainer] = -127;
	}
	motor[goalRetainer] = 0;

	//Lower goal lift & hoist
	while(SensorValue[liftQuad] > -210)
	{
		motor[leftLift] = -96;
		motor[rightLift] = 96;
		if(SensorValue[hoistQuad] > 90)
		{
			motor[leftHoist] = 16;
			motor[rightHoist] = -16;
		}
		else
		{
			motor[leftHoist] = -16;
			motor[rightHoist] = 16;
		}
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;

	//Drive backwards out of 20-point zone
	drive(-127, 0);
	wait1Msec(1000);
	stopDriving();
}

// ----------------------------------------------------------------- //
