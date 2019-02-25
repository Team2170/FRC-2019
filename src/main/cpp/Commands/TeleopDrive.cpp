// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/TeleopDrive.h"


TeleopDrive::TeleopDrive(): frc::Command(), 
driveMode((DriveMode) frc::Preferences::GetInstance()->GetInt("Drive Mode", arcadeDriveVoltage))
 {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain.get());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Called just before this Command runs the first time
void TeleopDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TeleopDrive::Execute()
{
    double xAxis = Robot::oi->getDriverJoystick()->GetX();
    double yAxis = Robot::oi->getDriverJoystick()->GetY();

    switch (driveMode)
    {

    case DriveMode::arcadeDriveVelocity:
        Robot::driveTrain->VelocityArcade(-yAxis, -xAxis);
        break;
    case DriveMode::tankDriveVelocity:
        Robot::driveTrain->VelocityTankDrive(-yAxis, -yAxis);
        break;
    case DriveMode::tankDriveVoltage:
        Robot::driveTrain->TankDrive(-yAxis, -yAxis);
        break;
    case DriveMode::arcadeDriveVoltage:
        Robot::driveTrain->ArcadeDrive(yAxis, xAxis);
        break;
    default:
        break;
    }
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopDrive::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void TeleopDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TeleopDrive::Interrupted() {

}
