#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

#include "MyRio.h"
#include "I2C.h"
#include "Motor_Controller.h"
#include "Utils.h"
#include "Ultrasonic.h"

#include <sys/time.h>

using namespace std;

extern NiFpga_Session myrio_session;

void waitForMilli (int usecs);

NiFpga_Status status;

int dd;

int main(int argc, char **argv)
{
  
    Ultrasonic ultrasonic;


	status = MyRio_Open();
	if (MyRio_IsNotSuccess(status))
	{
		return status;
	}

	MyRio_I2c i2c;
	status = Utils::setupI2CB(&myrio_session, &i2c);

	Motor_Controller mc = Motor_Controller(&i2c);
	mc.controllerEnable(DC);
	mc.controllerEnable(SERVO);

	int volt = mc.readBatteryVoltage(1);
	printf("%d\n\n", volt);

	int speed = 200;
	int rigthCount = 0;

	int loopTime = time(0) + 20; 
	while(time(0) < loopTime){
	
		dd = ultrasonic.getDistance();

		if(dd < 30)
		{

			printf("%d, Turning\n", dd);
			fflush(stdout);

			rigthCount = mc.readEncoderDegrees(DC, DC_1) + 465;
			mc.setMotorDegrees(DC, speed, rigthCount, 0, 0);
			
			Utils::waitFor(3);

		}else{
			printf("%d, Forward\n", dd);

			mc.setMotorSpeeds(DC, speed, -speed);
			Utils::waitFor(1);
			mc.setMotorSpeeds(DC, 0, -0);


		}
		fflush(stdout);


		//for(int i=100000000; i >0; i--);

	}

	mc.controllerReset(DC);
	mc.controllerReset(SERVO);

	status = MyRio_Close();

	return status;


	return 0;
}

void waitForMilli (int milli_seconds) {
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds);
  
}