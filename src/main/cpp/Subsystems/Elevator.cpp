// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Elevator.h"
#include "Commands/TeleopElevator.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/TeleopElevator.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elevator::Elevator() : frc::Subsystem("Elevator"),
    kP_Inner(frc::Preferences::GetInstance()->GetDouble("kP Inner", 6.0)),
    kD_Inner(frc::Preferences::GetInstance()->GetDouble("kD Inner", 600.0)),
    kI_Inner(frc::Preferences::GetInstance()->GetDouble("kI Inner", 0.0)),
    kF_Inner(frc::Preferences::GetInstance()->GetDouble("kF Inner", 0.0)),
    kP_Outer(frc::Preferences::GetInstance()->GetDouble("kP Outer", 0.3)),
    kD_Outer(frc::Preferences::GetInstance()->GetDouble("kD Outer", 1.0)),
    kI_Outer(frc::Preferences::GetInstance()->GetDouble("kI Outer", 0.0)),
    kF_Outer(frc::Preferences::GetInstance()->GetDouble("kF Outer", 0.0)),
    kP_Rear(frc::Preferences::GetInstance()->GetDouble("kP Rear", 0.0)),
    kD_Rear(frc::Preferences::GetInstance()->GetDouble("kD Rear", 0.0)),
    kI_Rear(frc::Preferences::GetInstance()->GetDouble("kI Rear", 0.0)),
    kF_Rear(frc::Preferences::GetInstance()->GetDouble("kF Rear", 0.0)),
    bMagic(frc::Preferences::GetInstance()->GetBoolean("Magic Elevator", false)) {

    // Both robots have "inner elevator"
    talonInnerFront.reset(new WPI_TalonSRX(9));
    talonInnerFront->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
    talonInnerFront->ConfigReverseLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_FeedbackConnector, LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 0);
    if (Robot::IsPracticeBot()) {
        talonInnerFront->SetInverted(true);
    }
    talonInnerFront->SetSensorPhase(false);
    talonInnerFront->SetSelectedSensorPosition(0, 0);
    talonInnerFront->Config_kP(0, kP_Inner);
    talonInnerFront->Config_kI(0, kI_Inner);
    talonInnerFront->Config_kD(0, kD_Inner);
    talonInnerFront->Config_kF(0, kF_Inner);
    talonInnerFront->ConfigMotionAcceleration(INNER_MAGIC_ACCEL);      // cnts/100 msec
    talonInnerFront->ConfigMotionCruiseVelocity(INNER_MAGIC_VELOCITY); // cnts/100 msec
//    talonInnerFront->ConfigClosedloopRamp(0.3);     // 0.3 seconds to full speed

    if (Robot::IsPracticeBot())
    {
        printf("Practice Elevator\n");
    }
    else
    {
        limitSwitchInnerTop.reset(new frc::DigitalInput(0));
        AddChild("Limit Switch Inner Top", limitSwitchInnerTop);

        limitSwitchInnerBottom.reset(new frc::DigitalInput(1));
        AddChild("Limit Switch Inner Bottom", limitSwitchInnerBottom);


        talonRear.reset(new WPI_TalonSRX(8));
        talonRear->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
        talonRear->SetSensorPhase(true);
        talonRear->SetSelectedSensorPosition(0, 0);

        sparkMaxOuter.reset(new rev::CANSparkMax(sparkElevatorID, rev::CANSparkMax::MotorType::kBrushless));
        pidOuter.reset(new rev::CANPIDController(sparkMaxOuter->GetPIDController()));
        sparkMaxOuterEncoder.reset(new rev::CANEncoder(sparkMaxOuter->GetEncoder()));

        // set scaling factor for position (since encoder is in motor)
        sparkMaxOuterEncoder->SetPositionConversionFactor((OUTER_SPROCKET_PITCH * M_PI) / OUTER_GEAR_RATIO);
        sparkMaxOuterEncoder->SetVelocityConversionFactor((OUTER_SPROCKET_PITCH * M_PI) / OUTER_GEAR_RATIO / 60.0);

        sparkMaxOuterEncoder->SetPosition(0.0);

        // Config PID gains for Spark Max Outer
        sparkMaxOuter->SetClosedLoopRampRate(0.3); // 0.3 seconds to ramp to full speed
        pidOuter->SetOutputRange(kMinOutput, kMaxOutput);
        pidOuter->SetP(kP_Outer);
        pidOuter->SetI(kI_Outer);
        pidOuter->SetD(kD_Outer);
        pidOuter->SetFF(kF_Outer);

        pidOuter->SetSmartMotionMaxVelocity(OUTER_MAGIC_VELOCITY);
        pidOuter->SetSmartMotionMaxAccel(OUTER_MAGIC_ACCEL);
    }
}

void Elevator::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new TeleopElevator());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Elevator::Periodic() {
    // Put code here to be run every loop
    ControlElevatorPositions();

    // put elevator positions on smartdash
    frc::SmartDashboard::PutNumber("Elevator Setpoint Inner (inches)", mInnerPosCmd);
    frc::SmartDashboard::PutNumber("Elevator Setpoint Outer (inches)", mOuterPosCmd);
}

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::ControlElevatorPositions() {
    if (Robot::IsPracticeBot()) {
        ControlInnerPosition(bMagic);
    }
    else {
        ControlInnerPosition(bMagic);
        ControlOuterPosition(bMagic);
        ControlRearPosition();
    }
}

void Elevator::ControlInnerPosition(bool bMagic) {
    // calculate in inches and convert to native counts for command setpoint
    mInnerPosCmd = fmax(mInnerPosCmd, kMinInnerPos);
    mInnerPosCmd = fmin(mInnerPosCmd, kMaxInnerPos);
    if (bMagic) {
        talonInnerFront->Set(ControlMode::MotionMagic, inchesToCountsInner(mInnerPosCmd));
    }
    else {    //Step input
        talonInnerFront->Set(ControlMode::Position, inchesToCountsInner(mInnerPosCmd));
    }
    frc::SmartDashboard::PutNumber("Inner Elevator", GetInnerPosInches());
    frc::SmartDashboard::PutNumber("Inner Elevator Cnts", GetInnerPos());
}

void Elevator::ControlOuterPosition(bool bMagic) {
    // calculate in inches and command in inches thanks to position scaling
    pidOuter->SetReference(mOuterPosCmd, rev::ControlType::kPosition);
    frc::SmartDashboard::PutNumber("Outer Elevator", GetOuterPosInches());
}

void Elevator::ControlRearPosition() {
    // calculate in inches and convert to native encoder units for setpoint
    talonRear->Set(ControlMode::Position, inchesToCountsRear(mRearPosCmd));
    frc::SmartDashboard::PutNumber("Rear Elevator", GetRearPosInches());
}

bool Elevator::InnerAtPosition() {
    bool atPositionWithDeadband = false;

    if (std::fabs(mInnerPosCmd - GetInnerPosInches()) < IN_POSITION_DEADBAND) {
        atPositionWithDeadband = true;
    }

    return atPositionWithDeadband;
}

bool Elevator::OuterAtPosition() {
    bool atPositionWithDeadband = false;

    // we will fix this later (sorry gang)
    if (std::fabs(mOuterPosCmd + GetOuterPosInches()) < IN_POSITION_DEADBAND) {
        atPositionWithDeadband = true;
    }
    
    return atPositionWithDeadband;
}

bool Elevator::RearAtPosition() {
    bool atPositionWithDeadband = false;

    if (std::fabs(mRearPosCmd - GetRearPosInches()) < IN_POSITION_DEADBAND) {
        atPositionWithDeadband = true;
    }
    
    return atPositionWithDeadband;
}

void Elevator::StopAllElevators() {
    StopInner();
    StopOuter();
    StopRear();
}

void Elevator::StopInner() {
    mInnerPosCmd = GetInnerPosInches();
    talonInnerFront->Set(ControlMode::MotionMagic, inchesToCountsInner(mInnerPosCmd));
}

void Elevator::StopRear() {
    mRearPosCmd = GetRearPosInches();
}

void Elevator::StopOuter() {
    mOuterPosCmd = GetOuterPosInches();
}

double Elevator::inchesToRotationsOuter(double inches){
    return inches / OUTER_SPROCKET_PITCH * OUTER_GEAR_RATIO;
}

double Elevator::rotationsToInchesOuter(double rotations) {
    return rotations * OUTER_SPROCKET_PITCH * M_PI;
}

double Elevator::GetInnerPosInches() {
    return countsToInchesInner(GetInnerPos());
}

double Elevator::GetRearPosInches() {
    // Implement this later!
}

double Elevator::GetOuterPosInches() {
    return -GetOuterPos();   // No need for math here because we have the scale factor
}

double Elevator::inchesToCountsInner(double inches) {
    return (inches / (INNER_SPROCKET_PITCH * M_PI) * ENCODER_CNTS_PER_REV);
}

double Elevator::countsToInchesInner(double counts) {
    return (counts / ENCODER_CNTS_PER_REV * (INNER_SPROCKET_PITCH * M_PI));
}

double Elevator::inchesToCountsRear(double inches) {
    return (inches / (REAR_SMALL_SPROCKET_PITCH * M_PI) * ENCODER_CNTS_PER_REV);
}

double Elevator::countsToInchesRear(double counts) {
    return (counts / ENCODER_CNTS_PER_REV * (REAR_SMALL_SPROCKET_PITCH * M_PI));
}

void Elevator::SlewInner(double slew) {
    double cmd = slew;
    bool stop = false;

    if (fabs(cmd) < 0.1) {
        cmd = 0.0;
        stop = true;
    } 
    cmd *= 20.0 * 0.02;
    if (stop) {
        if (!InnerAtPosition()) {
            StopInner();
        }
    }
    else {
        SetInnerPosition(Robot::elevator->GetInnerCmd() + cmd);
    }
}

void Elevator::SlewOuter(double slew) {
    double cmd = slew;
    bool stop = false;

    if (fabs(cmd) < 0.2) {
        cmd = 0.0;
        stop = true;
    } 
    cmd *= 20.0 * 0.02;

    if (stop) {
        if (!OuterAtPosition()) {
            StopOuter();
        }
    }
    else {
        SetOuterPosition(Robot::elevator->GetOuterPosInches() + cmd);
    }
}