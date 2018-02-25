/*--------------------------------------------------//--------------------------------------------------//

Team 9502, Liberty High School VEX Robotics
File: ../Includes/LCD2.0.h
Description: Contains LCD Code

//--------------------------------------------------//--------------------------------------------------*/

#include "../Include/A_autonomous_routines.h"

int refreshRate;
string selectString;
short routineNum = 0;

//Array of autonomous routine names
string routineNames[] =
{
	"   Do Nothing   ",
	"Mobile Goal  (R)",
	"  TEST PROGRAM  "
};

int numRoutines = sizeof(routineNames)/sizeof(routineNames[0]);

//--------------------------------------------------//--------------------------------------------------//

//Function to show/hide arrows on screen when necessary
void setSelectString()
{
	//If on the first, leftmost routine...
	if(routineNum == 0)
	{
		//Hide the left arrow
		selectString = ("     Select    >");
	}
	//Otherwise, if on the last, rightmost routine...
	else if(routineNum == (numRoutines - 1))
	{
		//Hide the right arrow
		selectString = ("<    Select     ");
	}
	//Else, if on one of the middle routines...
	else
	{
		//Show both left and right arrows
		selectString = ("<    Select    >");
	}
}

void setLCDRefreshRate(int inputRefreshRate)
{
	refreshRate = inputRefreshRate;
	return;
}

task autonomousSelector()
{
		// Turn on the LCD backlight, signifying that it needs input
	bLCDBacklight = true;

	// // While the robot is disabled...
	// // (Wouldn't want the robot to be stuck waiting for a program selection the whole match!)
	while(!bIfiRobotDisabled)
	{
		// Decide which arrows to show: left, right or both?
		setSelectString();

		//Display current autonomous routine name on the top line
		displayLCDCenteredString(0, routineNames[routineNum]);
		//Display "Select" on the bottom line
		displayLCDCenteredString(1, selectString);

		//If (the left LCD button is pressed) and (the currently displayed routine is not the first)...
		if(nLCDButtons == 1 && (routineNum > 0))
		{
			//Wait for button release
			while(nLCDButtons == 1)
			{
				//Do nothing
				EndTimeSlice();
			}
			//Go to the routine to the left
			routineNum--;
		}

		//Otherwise, if (the right LCD button is pressed) and (the currently displayed routine is not the last)...
		else if(nLCDButtons == 4 && (routineNum < (numRoutines - 1)))
		{
			//Wait for button release
			while(nLCDButtons == 4)
			{
				//Do nothing
				EndTimeSlice();
			}
			//Go to the routine to the right
			routineNum++;
		}

		//Otherwise, if the center LCD button is pressed...
		else if(nLCDButtons == 2)
		{
			break;
		}

		//Else, if no LCD buttons are pressed...
		else
		{
			//Do nothing
			EndTimeSlice();
		}

		//Refresh rate
		wait1Msec(1000.0/refreshRate);
	}

	displayLCDCenteredString(1, " ^  Selected  ^ ");
	bLCDBacklight = false;

	//End this task
	return;
}
