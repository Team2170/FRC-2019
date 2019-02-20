// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/DriveTrain.h"
#include "Commands/TeleopDrive.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/TeleopDrive.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain"),
                           kWheelDiameter(frc::Preferences::GetInstance()->GetDouble("Wheel Diameter", 6.0)),
                           kP_Vision(frc::Preferences::GetInstance()->GetDouble("kP Vision", 30.0))
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    powerDistributionPanel.reset(new frc::PowerDistributionPanel(0));
    AddChild("PowerDistributionPanel", powerDistributionPanel);
    

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    sparkMaxLeftLead.reset(new rev::CANSparkMax(leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless));
    sparkMaxLeftFollow.reset(new rev::CANSparkMax(leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless));
    sparkMaxRightLead.reset(new rev::CANSparkMax(rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless));
    sparkMaxRightFollow.reset(new rev::CANSparkMax(rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless));
    analogGyro.reset(new frc::ADXRS450_Gyro());
    differentialDrive.reset(new frc::DifferentialDrive(*sparkMaxLeftLead, *sparkMaxRightLead));

    // Set follower modes for sparkMax2 and sparkMax4
    sparkMaxLeftFollow->Follow(*sparkMaxLeftLead);
    sparkMaxRightFollow->Follow(*sparkMaxRightLead);

    pidControllerL.reset(new rev::CANPIDController(sparkMaxLeftLead->GetPIDController()));
    pidControllerR.reset(new rev::CANPIDController(sparkMaxRightLead->GetPIDController()));
    encoderControllerL.reset(new rev::CANEncoder(sparkMaxLeftLead->GetEncoder()));
    encoderControllerR.reset(new rev::CANEncoder(sparkMaxRightLead->GetEncoder()));

    // Set velocity scaling
    encoderControllerL->SetVelocityConversionFactor((M_PI * kWheelDiameter) / (kGearRatio * 60.0 * 12.0));
    encoderControllerR->SetVelocityConversionFactor((M_PI * kWheelDiameter) / (kGearRatio * 60.0 * 12.0));

    // Set min/max powers
    pidControllerL->SetOutputRange(kMinOutput, kMaxOutput);
    pidControllerR->SetOutputRange(kMinOutput, kMaxOutput);

    // Set kFF and kP (after tuning, since gains have already been determined)
    pidControllerL->SetP(kP);
    pidControllerR->SetP(kP);

    pidControllerL->SetFF(kFF);
    pidControllerR->SetFF(kFF);
}

void DriveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new TeleopDrive());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void DriveTrain::Periodic() {
    // Put code here to be run every loop
    differentialDrive->FeedWatchdog();
    frc::SmartDashboard::PutNumber("Drive Velocity", encoderControllerL->GetVelocity());

}

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::TankDrive(double left, double right) {
    differentialDrive->TankDrive(left, right);
}

void DriveTrain::ArcadeDrive(double xSpeed, double zRotation) 
{
    differentialDrive->ArcadeDrive(-xSpeed, zRotation);
}

void DriveTrain::VelocityArcade(double xSpeed, double zRotation, bool squaredInputs)
{
    double moveValue = -xSpeed;
    double rotateValue = zRotation;

    if(moveValue > 0.0 && moveValue < 0.05){
        moveValue = 0.0;
    } else if(moveValue < 0.0 && moveValue > -0.05){
        moveValue = 0.0;
    } 

    if(rotateValue > 0.0 && rotateValue < 0.05){
        rotateValue = 0.0;
    } else if(rotateValue > 0.0 && rotateValue < 0.05){
        rotateValue = 0.0;
    }

    static bool reported = false;
    if (!reported)
    {
        HAL_Report(HALUsageReporting::kResourceType_RobotDrive, 4,
                   HALUsageReporting::kRobotDrive_ArcadeStandard);
        reported = true;
    }

    // local variables to hold the computed PWM values for the motors
    double leftMotorOutput;
    double rightMotorOutput;

    // LeftMove and leftRotate limits to +-1.0
    if (moveValue > 1.0)
    {
        moveValue = 1.0;
    }
    if (moveValue < -1.0)
    {
        moveValue = -1.0;
    }
    if (rotateValue > 1.0)
    {
        rotateValue = 1.0;
    }
    if (rotateValue < -1.0)
    {
        rotateValue = -1.0;
    }

    // square the inputs (while preserving the sign) to increase fine control
    // while permitting full power
    if (squaredInputs)
    {
        moveValue = std::copysign(moveValue * moveValue, moveValue);
        rotateValue = std::copysign(rotateValue * rotateValue, rotateValue);
    }

    if (moveValue > 0.0)
    {
        if (rotateValue > 0.0)
        {
            leftMotorOutput = moveValue - rotateValue;
            rightMotorOutput = std::max(moveValue, rotateValue);
        }
        else
        {
            leftMotorOutput = std::max(moveValue, -rotateValue);
            rightMotorOutput = moveValue + rotateValue;
        }
    }
    else
    {
        if (rotateValue > 0.0)
        {
            leftMotorOutput = -std::max(-moveValue, rotateValue);
            rightMotorOutput = moveValue + rotateValue;
        }
        else
        {
            leftMotorOutput = moveValue - rotateValue;
            rightMotorOutput = -std::max(-moveValue, -rotateValue);
        }
    }

    double leftMotorSpeed = leftMotorOutput * maxFeetPerSec;
    double rightMotorSpeed = rightMotorOutput * maxFeetPerSec;

    // Send setpoints to pid controllers
    pidControllerL->SetReference(leftMotorSpeed, rev::ControlType::kVelocity);
    pidControllerR->SetReference(rightMotorSpeed, rev::ControlType::kVelocity);
}

void DriveTrain::VelocityTankDrive(double left, double right, bool squaredInputs) {
    static bool reported = false;
    if (!reported)
    {
        HAL_Report(HALUsageReporting::kResourceType_RobotDrive, 4,
                   HALUsageReporting::kRobotDrive_Tank);
        reported = true;
    }

    if (left > 1.0)
    {
        left = 1.0;
    }
    if (left < -1.0)
    {
        left = -1.0;
    }
    if (right > 1.0)
    {
        right = 1.0;
    }
    if (right < -1.0)
    {
        right = -1.0;
    }

    // square the inputs (while preserving the sign) to increase fine control
    // while permitting full power
    if (squaredInputs)
    {
        left = std::copysign(left * left, left);
        right = std::copysign(right * right, right);
    }

    double leftMotorSpeed = left * maxFeetPerSec;
    double rightMotorSpeed = right * -maxFeetPerSec;

    // Send setpoints to pid controllers
    pidControllerL->SetReference(leftMotorSpeed, rev::ControlType::kVelocity);
    pidControllerR->SetReference(rightMotorSpeed, rev::ControlType::kVelocity);
}

void DriveTrain::ClosedLoopVelocityControl(double speed)
{
    // read PID coefficients from SmartDashboard

    // // if PID coefficients on SmartDashboard have changed, write new values to controller
    // if(p != kP) {
    //     pidControllerL->SetP(p); kP = p;
    //     pidControllerR->SetP(p); kP = p;
    // }
    // if(i != kI) {
    //     pidControllerL->SetI(i); kI = i;
    //     pidControllerR->SetI(i); kI = i;
    // }
    // if(d != kD) {
    //     pidControllerL->SetD(d); kD = d;
    //     pidControllerR->SetD(d); kD = d;
    // }
    // if(iz != kIz) {
    //     pidControllerL->SetIZone(iz); kIz = iz;
    //     pidControllerR->SetIZone(iz); kIz = iz;
    // }
    // if(ff != kFF) {
    //     pidControllerL->SetFF(ff); kFF = ff;
    //     pidControllerR->SetFF(ff); kFF = ff;
    // }

    if (speed > 0.5)
    {
        speed = 0.5;
    }
    else if (speed < -0.5)
    {
        speed = -0.5;
    }
    //set the max speeds of the axis to 0.5.

    // read setpoint from joystick and scale by max rpm
    double setPointL = maxRPM * speed;
    double setPointR = maxRPM * -speed;

    // Send setpoints to pid controllers
    pidControllerL->SetReference(setPointL, rev::ControlType::kVelocity);
    pidControllerR->SetReference(setPointR, rev::ControlType::kVelocity);

    // Put editable PID values on Dashboard

    //std::cout << kFF << std::endl;
}

void DriveTrain::TankDriveVelocityError(double velocity, double error) {
    // double setPointL = -velocity_RPM - (kP_Vision * error);
    // double setPointR = velocity_RPM - (kP_Vision * error);
    double setPointL = velocity - (kP_Vision * error);
    double setPointR = velocity + (kP_Vision * error);

    pidControllerL->SetReference(setPointL, rev::ControlType::kVelocity);
    pidControllerR->SetReference(setPointR, rev::ControlType::kVelocity);
}
