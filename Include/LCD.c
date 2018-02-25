/*--------------------------------------------------//--------------------------------------------------//

Team 9502, Liberty High School VEX Robotics
File: ../Includes/LCD3.0.c
Description: Contains LCD Code

//--------------------------------------------------//--------------------------------------------------*/

//If team is A
#ifdef TEAM_A
	//Include A autonomous
  #include "A_autonomous_routines.h"
#endif
//If team is B
#ifdef TEAM_B
  //Include B autonomous
  #include "B_autonomous_routines.h"
#endif

int refreshRate = 20;
string selectString;
short routineNum = 0;

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

task autonomousSelector()
{
	// Turn on the LCD backlight, signifying that it needs input
	bLCDBacklight = true;

	// While the robot is not in autonomous mode or is disabled...
	while(!bIfiAutonomousMode || bIfiRobotDisabled)
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
