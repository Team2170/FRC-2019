// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/TeleopElevator.h"
#include <iostream>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

TeleopElevator::TeleopElevator(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::elevator.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void TeleopElevator::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TeleopElevator::Execute() {
    double cmdInner = -Robot::oi->getOperatorJoystick()->GetY(frc::GenericHID::JoystickHand::kLeftHand);
    double cmdOuter = -Robot::oi->getOperatorJoystick()->GetY(frc::GenericHID::JoystickHand::kRightHand);
    bool stopInner = false;
    bool stopOuter = false;

    if (fabs(cmdInner) < 0.2)
    {
        cmdInner = 0.0;
        stopInner = true;
    } 
    cmdInner *= 20.0 * 0.02;

    if (fabs(cmdOuter) < 0.2)
    {
        cmdOuter = 0.0;
        stopOuter = true;
    } 
    cmdOuter *= 20.0 * 0.02;

    //std::cout << "called" << std::endl;
    if (stopInner) {
    }
    else {
    Robot::elevator->SetInnerPosition(Robot::elevator->GetInnerPosInches() + cmdInner);
    }
 
    if (stopOuter) {
    }
    else {
        Robot::elevator->SetOuterPosition(Robot::elevator->GetOuterPosInches() + (cmdOuter * 10));
    }
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopElevator::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void TeleopElevator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TeleopElevator::Interrupted() {

}
