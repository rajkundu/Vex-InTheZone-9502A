int deadZone(int inputVal, int deadZoneVal)
{
	if(fabs(inputVal) > deadZoneVal)
	{
		return inputVal;
	}
	else
	{
		return 0;
	}
}

task hoistPID()
{
	float kp = 5.0;
	float kd = 3.0;
	float ki = 0.0;

	float targetPosition = 0;
	float hoistInput = 0;
	int error = 0;
	int error_derivative = 0;
	int error_integral = 0;

	float lastError = 0;
	float integralActiveZone = 10.0;

	string lcdDebugString;

	while(true)
	{
		error = targetPosition - SensorValue[hoistQuad];
		error_derivative = error - lastError;
		error_integral += (((abs(error) < integralActiveZone)) ? error : 0);

		motor[leftHoist] = -(motor[rightHoist] = kp*error + kd*error_derivative + ki*error_integral);

		lastError = error;

		hoistInput = deadZone(vexRT[Ch2Xmtr2], 16) / 5000.0;
		targetPosition += ((targetPosition <= 0) && (hoistInput < 0)) ? 0 : hoistInput;

		//Debug
		/*sprintf(lcdDebugString, "%f", error);
		displayLCDCenteredString(0, lcdDebugString);
		sprintf(lcdDebugString, "%f", error_integral);
		displayLCDCenteredString(1, lcdDebugString);*/
	}
}
