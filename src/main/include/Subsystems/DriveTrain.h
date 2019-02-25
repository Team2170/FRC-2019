// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H
#include "frc/commands/Subsystem.h"
#include "frc/WPILib.h"
#include "rev/CANSparkMax.h"
#include "hal/HAL.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DriveTrain: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<frc::PowerDistributionPanel> powerDistributionPanel;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static const int leftLeadDeviceID = 4, rightLeadDeviceID = 1, leftFollowDeviceID = 3, rightFollowDeviceID = 2;
	std::shared_ptr<frc::DifferentialDrive> differentialDrive;
	std::shared_ptr<rev::CANSparkMax> sparkMaxLeftLead;
	std::shared_ptr<rev::CANSparkMax> sparkMaxLeftFollow;
	std::shared_ptr<rev::CANSparkMax> sparkMaxRightLead;
	std::shared_ptr<rev::CANSparkMax> sparkMaxRightFollow;
	std::shared_ptr<frc::ADXRS450_Gyro> analogGyro;
	std::shared_ptr<rev::CANPIDController> pidControllerL;
	std::shared_ptr<rev::CANPIDController> pidControllerR;
	std::shared_ptr<rev::CANEncoder> encoderControllerL;
	std::shared_ptr<rev::CANEncoder> encoderControllerR;

	const double kGearRatio = 5.95;
	const double kWheelDiameter;

	// PID Gains for closed-loop velocity control
	const double kP, kI = 0, kD = 0, kIz = 0, kFF, kMaxOutput = 1, kMinOutput = -1;
	
	// Max RPM for motors
	const double maxRPM = 5600;
	const double maxFeetPerSec;

	// PID Gains for closed-loop velocity control FOR VISION 
	const double kP_Vision;

public:
	DriveTrain();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void TankDrive(double left, double right);
	void ArcadeDrive(double xSpeed, double zRotation);
	void StopMotors(void);
	void VelocityArcade(double xSpeed, double zRotation, bool squaredInputs = true);
	void VelocityTankDrive(double left, double right, bool squaredInputs = true);
	void ClosedLoopVelocityControl(double speed);
	void TankDriveVelocityError(double velocity, double error);
	double GetVelocity();	

	// Gyro methods
	void ResetGyro()  { analogGyro->Reset();}
	double GetGyroAngle() {return analogGyro->GetAngle();}

	double FPStoRPM(double fps);
	double RPMtoFPS(double rpm);
};

#endif
