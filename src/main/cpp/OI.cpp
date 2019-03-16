// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "frc/smartdashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/ElevatorInnerPos.h"
#include "Commands/ElevatorOuterPos.h"
#include "Commands/ElevatorRearPos.h"
#include "Commands/GotoIntakePosition.h"
#include "Commands/InitRobot.h"
#include "Commands/IntakeDown.h"
#include "Commands/IntakeToggle.h"
#include "Commands/IntakeUp.h"
#include "Commands/PlaceHatch.h"
#include "Commands/TeleopDrive.h"
#include "Commands/TeleopElevator.h"
#include "Commands/TeleopIntake.h"
#include "Commands/TeleopOuttake.h"
#include "Commands/VisionDrive.h"
#include "Commands/ToggleCameraExposure.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/DropHatch.h"
#include "Commands/RaiseRobot.h"
#include "Commands/ClimbHighPlatform.h"
#include "Commands/ClimbLowPlatform.h"
#include "Commands/DriveStraightDistance.h"
#include "Commands/ElevatorInnerOuterPos.h"

/**
 * @brief Construct a new OI::OI object
 * 
 * 1. Initialize all push buttons (on push button panel)
 * 2. Initialize buttons for rotate commands
 * 3. Initialize buttons on driver joystick for hatch drop, vision lock, exposure toggle,
 *    intake/outtake, and raising robot
 */
OI::OI() {
    // Process operator interface input here.
//    pushbuttonPanel.reset(new frc::Joystick(2));
    
    if (Robot::IsPracticeBot()) {
      printf("Practice OI\n");
      frc::SmartDashboard::PutData("Hatch L1", new ElevatorInnerPos(Robot::elevator->kHatchL1, false));
      frc::SmartDashboard::PutData("Hatch L2", new ElevatorInnerPos(Robot::elevator->kHatchL2, false));
      frc::SmartDashboard::PutData("Cargo L1", new ElevatorInnerPos(Robot::elevator->kCargoL1, false));
      frc::SmartDashboard::PutData("Cargo L2", new ElevatorInnerPos(Robot::elevator->kCargoL2, false));
    }
    else {
      frc::SmartDashboard::PutData("Cargo L3", new ElevatorInnerOuterPos(Robot::elevator->kCargoL3, Robot::elevator->kHatchL2+3.0));
      frc::SmartDashboard::PutData("Cargo L2", new ElevatorInnerOuterPos(Robot::elevator->kCargoL2, Robot::elevator->kHatchL2));
      frc::SmartDashboard::PutData("Cargo L1", new ElevatorInnerOuterPos(Robot::elevator->kCargoL1, Robot::elevator->kOuterHome));
      frc::SmartDashboard::PutData("Hatch L3", new ElevatorInnerOuterPos(Robot::elevator->kHatchL3, Robot::elevator->kHatchL2));
      frc::SmartDashboard::PutData("Hatch L2", new ElevatorInnerOuterPos(Robot::elevator->kInnerHome+2, Robot::elevator->kHatchL2));
      frc::SmartDashboard::PutData("Hatch L1", new ElevatorInnerOuterPos(Robot::elevator->kHatchL1, Robot::elevator->kOuterHome));

      frc::SmartDashboard::PutData("Climb High", new ClimbHighPlatform());
      frc::SmartDashboard::PutData("Climb Low", new ClimbLowPlatform());
    }

   driverJoystick.reset(new frc::Joystick(0));

   if (Robot::IsTankDrive()) {
       driverJoystickRight.reset(new frc::Joystick(3));
   }

   operatorJoystick.reset(new frc::XboxController(1));

   // driver joystick button setups
   joystickDriverButtonHatchDrop.reset(new frc::JoystickButton(driverJoystick.get(), 1));
   joystickDriverButtonHatchDrop->WhenPressed(new DropHatch());
	joystickDriverButtonVisionLock.reset(new frc::JoystickButton(driverJoystick.get(), 2));
   joystickDriverButtonVisionLock->WhileHeld(new VisionDrive());
//	joystickDriverButtonForward.reset(new frc::JoystickButton(driverJoystick.get(), 3));
//   joystickDriverButtonForward->WhenPressed(new DriveStraightDistance(2.0));
   joystickDriverButtonExposureToggle.reset(new frc::JoystickButton(driverJoystick.get(), 3));
   joystickDriverButtonExposureToggle->WhenPressed(new ToggleCameraExposure());


   if (!Robot::IsPracticeBot()) {
      joystickButtonToggleIntake.reset(new frc::JoystickButton(operatorJoystick.get(), 3));
      joystickButtonToggleIntake->WhenPressed(new IntakeToggle());
      joystickButtonOuttake.reset(new frc::JoystickButton(operatorJoystick.get(), 2));
      joystickButtonOuttake->WhileHeld(new TeleopOuttake());
      joystickButtonIntake.reset(new frc::JoystickButton(operatorJoystick.get(), 1));
      joystickButtonIntake->WhileHeld(new TeleopIntake());
      joystickButtonRaiseRobot.reset(new frc::JoystickButton(operatorJoystick.get(), 4));
      joystickButtonRaiseRobot->WhenPressed(new ClimbHighPlatform());
   }
   else {
      printf("Intake Buttons Bypassed\n");
   }
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

/**
 * @brief Get the left driver joystick pointer
 * 
 * @return std::shared_ptr<frc::Joystick> 
 */
std::shared_ptr<frc::Joystick> OI::getDriverJoystick() {
   return driverJoystick;
}

/**
 * @brief Get the push button panel pointer
 * 
 * @return std::shared_ptr<frc::Joystick> 
 */
std::shared_ptr<frc::Joystick> OI::getPushbuttonPanel() {
   return pushbuttonPanel;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

/**
 * @brief Get the operator joystick pointer
 * 
 * @return std::shared_ptr<frc::Joystick> 
 */
std::shared_ptr<frc::XboxController> OI::getOperatorJoystick() {
   return operatorJoystick;
}

/**
 * @brief Get the right driver joystick pointer
 * 
 * @return std::shared_ptr<frc::Joystick> 
 */
std::shared_ptr<frc::Joystick> OI::getDriverJoystickRight() {
   return driverJoystickRight;
}
