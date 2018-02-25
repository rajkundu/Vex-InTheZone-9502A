#pragma config(Sensor, dgtl2,  goalLiftPistons, sensorDigitalOut)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftMotors,    tmotorNone, openLoop)
#pragma config(Motor,  port5,           turretMotors,  tmotorNone, openLoop)
#pragma config(Motor,  port7,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           backRight,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	int x = 0;
	int y = 0;
	int r = 0;
	while(true)
	{
		//----------------------
		// Driver Controller
		//----------------------

		//Drivetrain

		if(vexRT[Btn5U] == 1)
		{
			r = -64;
		}
		else if(vexRT[Btn6U] == 1)
		{
			r = 64;
		}
		else
		{
			r = 0;
		}

		x = vexRT[Ch4];
		y = vexRT[Ch3];
		motor[frontLeft] = x + y + r;
		motor[backLeft] = -x + y + r;
		motor[frontRight] = x - y + r;
		motor[backRight] = -x - y + r;

		//----------------------
		// Partner Controller
		//----------------------

		//Pistons
		//0 = Up
		//1 = Down
		if(vexRT[Btn6UXmtr2] == 1)
		{
			//Raise the piston lift
			SensorValue[goalLiftPistons] = 0;
			SensorValue[goalLiftPistons] = 0;
		}
		else if(vexRT[Btn5UXmtr2] == 1)
		{
			//Lower the piston lift
			SensorValue[goalLiftPistons] = 1;
			SensorValue[goalLiftPistons] = 1;
		}
		else
		{
			//Don't do anything, leave the piston where it is
			EndTimeSlice();
		}

		// - = open claw
		// + = close claw
		motor[clawMotor] = -(vexRT[Ch1Xmtr2] / 2.0);

		//Lift
		motor[liftMotors] = vexRT[Ch3Xmtr2];

		//Turret
		motor[turretMotors] = vexRT[Ch4Xmtr2];
	}
}
