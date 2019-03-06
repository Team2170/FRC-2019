// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H

#include "frc/WPILib.h"

class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<frc::Joystick> pushbuttonPanel;
	std::shared_ptr<frc::JoystickButton> pushButtonBlue3;
	std::shared_ptr<frc::JoystickButton> pushButtonBlue2;
	std::shared_ptr<frc::JoystickButton> pushButtonBlue1;
	std::shared_ptr<frc::JoystickButton> pushButtonRed3;
	std::shared_ptr<frc::JoystickButton> pushButtonRed2;
	std::shared_ptr<frc::JoystickButton> pushButtonRed1;
	std::shared_ptr<frc::Joystick> driverJoystick;
	std::shared_ptr<frc::JoystickButton> counterClockwiseTurn;
	std::shared_ptr<frc::JoystickButton> clockwiseTurn;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	std::shared_ptr<frc::XboxController> operatorJoystick;
	std::shared_ptr<frc::Joystick> driverJoystickRight;

	std::shared_ptr<frc::JoystickButton> joystickButtonToggleIntake;
	std::shared_ptr<frc::JoystickButton> joystickButtonOuttake;
	std::shared_ptr<frc::JoystickButton> joystickButtonIntake;
	std::shared_ptr<frc::JoystickButton> joystickButtonRaiseRobot;

	std::shared_ptr<frc::JoystickButton> joystickDriverButtonHatchDrop;
	std::shared_ptr<frc::JoystickButton> joystickDriverButtonVisionLock;
	std::shared_ptr<frc::JoystickButton> joystickDriverButtonClimbHigh;
	std::shared_ptr<frc::JoystickButton> joystickDriverButtonForward;

public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<frc::Joystick> getDriverJoystick();
	std::shared_ptr<frc::Joystick> getPushbuttonPanel();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<frc::XboxController> getOperatorJoystick();
	std::shared_ptr<frc::Joystick> getDriverJoystickRight();
};

#endif
