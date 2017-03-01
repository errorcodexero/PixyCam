#include <iostream>
#include <memory>
#include <string>

#include <SampleRobot.h>
#include <DigitalOutput.h>

#include "Pixy.h"

#ifdef PIXY_UART
#include "PixyUART.h"
#endif

#ifdef PIXY_TCP
#include "PixyTCP.h"
#endif

using namespace Pixy;

class Robot: public frc::SampleRobot {

private:
#ifdef PIXY_UART
    PixyUART uart;
#endif
#ifdef PIXY_TCP
    PixyTCP tegra;
#endif
    PixyCam camera;
    frc::DigitalOutput illuminator;

public:
    Robot() :
#ifdef PIXY_UART
	uart("/dev/ttyS1"), camera( uart ),
#endif
#ifdef PIXY_TCP
	tegra("tegra-ubuntu.local", "6425"), camera( tegra ),
#endif
	illuminator(10)
	{
	;
    }

    void RobotInit() {
	;
    }

    void Disabled() override {
	camera.disable();
	illuminator.Set(0);
    }

    void Autonomous() override {
	illuminator.Set(1);
	camera.enable();
	int frame = 0;
	while (IsAutonomous() && IsEnabled()) {
	    if (camera.isNewData()) {
		std::vector<Block> blocks = camera.getBlocks();
		std::cout << "frame " << ++frame << ": "
			  << blocks.size() << " blocks:" << std::endl;
		for (std::vector<Block>::const_iterator it = blocks.begin();
		      it != blocks.end(); it++)
		{
		    std::cout << *it << std::endl;
		}
		std::cout << std::endl;
	    }
	}
	camera.disable();
	illuminator.Set(0);
    }

    /*
     * Runs the motors with arcade steering.
     */
    void OperatorControl() override {
	;
    }

    /*
     * Runs during test mode
     */
    void Test() override {
	;
    }
};

START_ROBOT_CLASS(Robot)
