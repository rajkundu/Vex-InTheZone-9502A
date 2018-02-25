/*--------------------------------------------------//--------------------------------------------------//

Team 9502, Liberty High School VEX Robotics Team
File: LCD.h
Description: Contains code for LCD Display

//--------------------------------------------------//--------------------------------------------------*/

//Array of autonomous routine names
string routineNames[] =
{
	"   Do Nothing   "
};

//"Select" string to be shown on bottom line of LCD
string selectString;

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
	else if(routineNum == (sizeof(routineNames) - 1))
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

//--------------------------------------------------//--------------------------------------------------//

void flashOnLCD(string *textTopLine, string *textBottomLine, int time, short numTimes)
{
	//Run a loop that runs (numTimes) times
	for(short i = 0; i < numTimes; i++)
	{
		//Only clear the top line if (textTopLine) contains text
		if(*textTopLine != "\0")
		{
			clearLCDLine(0);
		}
		//Only clear the bottom line if (textBottomLine) contains text
		if(*textBottomLine != "\0")
		{
			clearLCDLine(1);
		}
		//Wait (time) milliseconds before showing the text
		wait1Msec(time);
		//Only display (textTopLine) on the top line if it contains text
		if(*textTopLine != "\0")
		{
			displayLCDCenteredString(0, *textTopLine);
		}
		//Only display (textBottomLine) on the bottom line if it contains text
		if(*textBottomLine != "\0")
		{
			displayLCDCenteredString(1, *textBottomLine);
		}
		//Wait (time) milliseconds before hiding the text
		wait1Msec(time);
	}
}

task autonomousSelector()
{
	bool autonomousSelected = false;

	// Turn on the LCD backlight, signifying that it needs input
	bLCDBacklight = true;

	// While the robot is disabled and the autonomous routine has not yet been selected...
	// (Wouldn't want the robot to be stuck waiting for a program selection the whole match!)
	while((bIfiRobotDisabled) && (!autonomousSelected))
	{
		// Decide which arrows to show: left, right or both?
		setSelectString();

		//Display current autonomous routine name on the top line
		displayLCDCenteredString(0, routineNames[routineNum]);
		//Display prompt to select on the bottom line
		displayLCDCenteredString(1, selectString);

		//If (the left LCD button is pressed) and (the currently displayed routine is not the first)...
		if((nLCDButtons == 1) && (routineNum > 0))
		{
			//Wait for button release
			while((nLCDButtons == 4) || (vexRT[Btn5U] == 1))
			{
				//Do nothing
				EndTimeSlice();
			}
			//Go to the routine to the left
			routineNum--;
		}

		//Otherwise, if (the right LCD button is pressed) and (the currently displayed routine is not the last)...
		else if((nLCDButtons == 4) && (routineNum < (sizeof(routineNames) - 1)))
		{
			//Wait for button release
			while((nLCDButtons == 4) || (vexRT[Btn6U] == 1))
			{
				//Do nothing
				EndTimeSlice();
			}
			//Go to the routine to the right
			routineNum++;
		}

		//Otherwise, if the center LCD button is pressed...
		else if((nLCDButtons == 2))
		{
			// Notify that program has been selected
			displayLCDString(0, 0, "Routine Selected");
			// Break the loop
			autonomousSelected = true;
		}

		//Else, if no LCD buttons are pressed...
		else
		{
			//Do nothing
			EndTimeSlice();
		}
	}

	//Turn off the LCD backlight, signifying that it does not need any input
	bLCDBacklight = false;

	//End this task
	return;
}
