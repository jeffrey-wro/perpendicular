
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "DIO.h"
#include "MyRio.h"
#include "I2C.h"
#include "Motor_Controller.h"
#include "Utils.h"


#include <sys/time.h>

#include "Ultrasonic.h"

extern NiFpga_Session myrio_session;


NiFpga_Status status;


int main(int argc, char **argv)
{
    NiFpga_Status status;

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

    printf("Starting");
    fflush(stdout);


    float leftDistance;
    float rightDistance;

    float calib = 0.75;

    int speed = 25;

    while(1) {

        leftDistance = ultrasonic.getDistance(Ultrasonic::FRONT_RIGHT);
        //printDistance((char *)"Right distance = ", leftDistance);
        rightDistance = ultrasonic.getDistance(Ultrasonic::FRONT_LEFT);
        //printDistance((char *)"Left distance = ", rightDistance);

        if(leftDistance >= 400 || leftDistance <= 2 || rightDistance >= 400 || rightDistance <= 2 ){
        	
			mc.setMotorSpeeds(DC, 0, 0);
        	printf("One sensor is Out of range\n");

        }else if(leftDistance - calib > rightDistance){

        	printf("Turning right\n");
			mc.setMotorSpeeds(DC, speed, speed);

        }else  if(leftDistance < rightDistance - calib){

        	printf("Turning left\n");
			mc.setMotorSpeeds(DC, -speed, -speed);

        }else{
			
			mc.setMotorSpeeds(DC, 0, 0);
        	printf("Robot is perpendicular to the surface\n");

        }


        usleep(100000);
    }

    status = MyRio_Close();

    
    return status;
}