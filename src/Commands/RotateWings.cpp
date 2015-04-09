// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "RotateWings.h"

RotateWings::RotateWings(float direction, float time) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::eagleWings);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	this->direction = direction;
	this->time = time;
}

// Called just before this Command runs the first time
void RotateWings::Initialize() {
	startTime = Timer::GetFPGATimestamp();
}

// Called repeatedly when this Command is scheduled to run
void RotateWings::Execute() {
	Robot::eagleWings->wingRotater->Set(direction);
}


// Make this return true when this Command no longer needs to run execute()
bool RotateWings::IsFinished() {
	return Timer::GetFPGATimestamp()>=startTime+time;
}

// Called once after isFinished returns true
void RotateWings::End() {
	Robot::eagleWings->wingRotater->Set(0);
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateWings::Interrupted() {
//	Robot::eagleWings->wingRotater->Set(0);
}
