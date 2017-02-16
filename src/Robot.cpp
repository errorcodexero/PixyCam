#include <iostream>
#include <memory>
#include <string>

#include <SampleRobot.h>

#include "Pixy.h"
#include "PixyUART.h"

using namespace Pixy;

class Robot: public frc::SampleRobot {

private:
    PixyUART uart;
    PixyCam camera;

public:
    Robot() : uart("/dev/ttyS1"), camera( uart ) {
	;
    }

    void RobotInit() {
	;
    }

    void Disabled() override {
	camera.disable();
    }

    void Autonomous() override {
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
