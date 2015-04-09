// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Drivetrain.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	rearRight = RobotMap::drivetrainrearRight;
	frontLeft = RobotMap::drivetrainfrontLeft;
	rearLeft = RobotMap::drivetrainrearLeft;
	frontRight = RobotMap::drivetrainfrontRight;
	robotDrive = RobotMap::drivetrainrobotDrive;
	driveGyro = RobotMap::drivetraindriveGyro;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	leftSonar = RobotMap::drivetrainleftSonar;
	rightSonar = RobotMap::drivetrainrightSonar;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	xScalar = 0.5;
	yScalar = 0.5;
	rotationScalar = 0.5;
	quadraticScaling = true;
	fastMode = true;
	fastModeMultiplier = 2.0;
}
void Drivetrain::ResetHeading() {
	driveGyro->Reset();
}
double Drivetrain::CorrectionAngle(double correctionConstant) {
	//TODO: code to detect gyroscope failure + fall-back mode (hard-coded constants)
	if(SmartDashboard::GetBoolean("autonUseGyro")){
		double gyroAngle = driveGyro->GetAngle();
		if(fabs(gyroAngle) < 10){
			printf("gyroAngle: %f\n",gyroAngle);
			SmartDashboard::PutBoolean("gyroIgnored",false);
			return -0.02 * gyroAngle;
			//TODO: refactor
		}
		else {
			printf("gyro error too high");
			SmartDashboard::PutBoolean("gyroIgnored",true);
			return 0;
		}
	}
	else {
		printf("not using gyroscope");
	}
	return 0;

}
void Drivetrain::DriveOnHeading(double velocity, double correctionConstant) {
//	if(velocity > 0){
//		correctionAngle = CorrectionAngle(correctionConstant) * CorrectionAngle(correctionConstant);
//	}
//	RobotMap::drivetrainrobotDrive->MecanumDrive_Polar(velocity,0,correctionAngle);
	if(velocity>0){
		correctionConstant = correctionConstant * correctionConstant;
	}
	RobotMap::drivetrainrobotDrive->MecanumDrive_Polar(velocity,0,CorrectionAngle(correctionConstant));
	}
void Drivetrain::toggleFastMode() {
	fastMode = !fastMode;
}

void Drivetrain::DriveTeleop(double x, double y, double r) {
	if(quadraticScaling) {
		x = x*fabs(x);
		y = y*fabs(y);
		r = r*fabs(r);
	}
	x *= xScalar;
	y *= yScalar;
	r *= rotationScalar;
	if(fastMode) {
		x *= fastModeMultiplier;
		y *= fastModeMultiplier;
		r *= fastModeMultiplier;
	}
	RobotMap::drivetrainrobotDrive->MecanumDrive_Cartesian(x,y,r);
}
void Drivetrain::InitDefaultCommand() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
