// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include "Timer.h"
#include "Diagnostics.h"
#include "xbox.h"
#include "Commands/AutonCalibration.h"
#include "Commands/RunLift.h"
#include "I2C.h"
#define DEBUG_LOGGING


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
EagleWings* Robot::eagleWings = 0;
Drivetrain* Robot::drivetrain = 0;
Lift* Robot::lift = 0;
StepDetectorator* Robot::stepDetectorator = 0;
Compresoratoror* Robot::compresoratoror = 0;
CanStashinator* Robot::canStashinator = 0;
OI* Robot::oi = 0;
I2C* Robot::i2c = 0;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
Aligner* Robot::aligner = 0;
DigitalInput* liftDetectorator1 = RobotMap::liftDetectorator1;


void Robot::startDiagnosticLogging() {
	//starts logging and prints headers
	startLogging();
	///print header for log
	bufferPrintf("Gyro, Acc X, Acc Y\n");
}
void Robot::logRow() {
	//	bufferPrintf("%f, %f, %f\n",RobotMap::drivetraindriveGyro->GetAngle(),
	//			stepDetectorator->accelerometer->GetX(), stepDetectorator->accelerometer->GetY());
	//	printf("Acc x: %f Acc y: %f", stepDetectorator->accelerometer->GetX(), stepDetectorator->accelerometer->GetY());
		DashboardPrintf("Acc x:","%f",stepDetectorator->accelerometer->GetX());
		DashboardPrintf("Gyro Value:","%f",drivetrain->driveGyro->GetAngle());
	SmartDashboard::PutNumber("encoderValue", Robot::lift->encoder->Get());

}
void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	eagleWings = new EagleWings();
	drivetrain = new Drivetrain();
	stepDetectorator = new StepDetectorator();
	compresoratoror = new Compresoratoror();
	canStashinator = new CanStashinator();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	resetLift = new ResetLift();
	lift = new Lift(resetLift);
	aligner = new Aligner();
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = new OI();
	lw = LiveWindow::GetInstance();
	//	CameraServer::GetInstance()->SetQuality(50);
	//	CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutonomousCommand();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	//	autonomousCommand = new GatherCans();
	autonCalibration = new AutonCalibration();
	alignWithStep = new AlignWithStep();
	backupToAutonZone = new BackupToAutonZone();
//	driveForward = new DriveForward();
	//	gatherCans = new GatherCans();
	lowerOneTote = new LowerOneTote();
	raiseOneTote = new RaiseOneTote();
	raiseWings = new RaiseWings();
	retractWings = new RetractWings();
	push = new APusH();
	gearUp = new ShiftToHighGear();
	gearDown = new ShiftToLowGear();
	pull = new UnAPusH();
	pidLift = new PIDLift();
	deployAligner = new DeployAligner();
	retractAligner = new RetractAligner();
	rotateWingsForward = new RotateWings(.2,.5);
	rotateWingsBackward = new RotateWings(-.2,.5);
	driverStick = new Joystick(0);
	techStick = new Joystick(1);
	raiseLift = new RunLift(0.5);
	lowerLift = new RunLift(-0.5);
	stopLift = new RunLift(0);
	runConveyor = new RunConveyor();
	stopConveyor = new StopConveyor();
	raiseStash = new LiftCanStashinator();
	lowerStash = new LowerCanStashinator();
	//TODO: add code to ensure gyroscope has initialized
	RobotMap::drivetraindriveGyro->InitGyro();	//probably takes 10 seconds
	//auton testing code...3/28
	SmartDashboard::PutNumber("autonForwardSpeed", .4);
	SmartDashboard::PutNumber("autonJerkSpeed", 1);
	SmartDashboard::PutNumber("autonTimeout", 2);
	SmartDashboard::PutNumber("autonDriveBackSpeed", .6);
	SmartDashboard::PutNumber("autonRotateTime", 2);
	SmartDashboard::PutNumber("autonRotateSpeed", .2);
	SmartDashboard::PutNumber("autonDriveBackTime", 5.25);
	SmartDashboard::PutNumber("BackupCorrectionConstant", 0.3);
	SmartDashboard::PutNumber("AutonJerkyCorrectionConstant", 0.8);
	SmartDashboard::PutNumber("DriveForwardCorrectionConstant", 0.02);
	startDiagnosticLogging();
	SetupRobot();
}
void Robot::SetupRobot() {
	deployToggle = -1;
	alignTime = 0;
	conveyorTime = 0;
	driveMultiplier = .5;
	driveToggleTime = 0;
	Robot::lift->gearboxShifter->Set(DoubleSolenoid::kForward);
	i2c = new I2C(I2C::Port::kOnboard,4);
}
void Robot::DisabledInit(){
	SmartDashboard::PutBoolean("resetGyro", false);
	SmartDashboard::PutBoolean("autonUseGyro",true);
	SmartDashboard::PutBoolean("In High Gear", Robot::lift->gearboxShifter->Get() == DoubleSolenoid::kForward);
	flushToDisk();
}
void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	if(SmartDashboard::GetBoolean("resetGyro")){
		Robot::drivetrain->driveGyro->InitGyro();
		SmartDashboard::PutBoolean("resetGyro", false);
	}
	int toSend = (int)(0 + (42-0) * (Robot::lift->encoder->Get() - - 173) / (1822 - -173));
	lightPattern[0] = toSend;
	i2c->Transaction(lightPattern,1,NULL,0);
	logRow();
	autonUseGyro = SmartDashboard::GetBoolean("autonUseGyro");
}
void Robot::AutonomousInit() {
		int autonNumber = SmartDashboard::GetNumber("autonNumber");
		double autonForwardSpeed = SmartDashboard::GetNumber("autonForwardSpeed");
		double autonJerkSpeed = SmartDashboard::GetNumber("autonJerkSpeed");
		double autonTimeout = SmartDashboard::GetNumber("autonTimeout");
		double autonDriveBackSpeed = SmartDashboard::GetNumber("autonDriveBackSpeed");
		double autonRotateTime = SmartDashboard::GetNumber("autonRotateTime");
		double autonRotateSpeed = SmartDashboard::GetNumber("autonRotateSpeed");
		double autonDriveBackTime = SmartDashboard::GetNumber("autonDriveBackTime");
	//	DashboardPrintf("autonNumber","%d", autonNumber);
//	int autonNumber = 1;
	autonomousCommand = new GatherCans(autonNumber,  autonForwardSpeed,  autonJerkSpeed,  autonTimeout,  autonDriveBackSpeed,  autonRotateTime,  autonRotateSpeed,  autonDriveBackTime);
	autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	Scheduler::GetInstance()->Run();
	int toSend = (int)(0 + (42-0) * (Robot::lift->encoder->Get() - - 173) / (1822 - -173));
	lightPattern[0] = toSend;
	i2c->Transaction(lightPattern,1,NULL,0);
		logRow();
}

void Robot::TeleopInit() {
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
	//TODO: put this in a reset method that is shared with autoninit
	RobotMap::drivetraindriveGyro->Reset();
	SmartDashboard::GetNumber("autonNumber");
	lightPattern[0] = 1;
	i2c->Transaction(lightPattern,1,NULL,0);
	Robot::lift->gearboxShifter->Set(DoubleSolenoid::kReverse);
//	gearDown->Start();
//	Robot::lift->limitSwitch->DisableInterrupts();
}

//Jeanette:  I THINK if we get rid of the or isRunning
//if a command needs PID it should enable it
//if a command doesn't want PID it should disable it
//otherwise, stop the lift if and only if PID is disabled /--
bool Robot::isNewPress(double time1, double time2) {
	return fabs(time1-time2) > .25;
}

LiftState Robot::getLiftState() {
	double currentTime = Timer::GetFPGATimestamp();
	if(driverStick->GetRawAxis(RIGHT_TRIGGER) > 0.5 || techStick->GetRawAxis(RIGHT_TRIGGER) > 0.5)
		return ManualRaisingLift;
	if(driverStick->GetRawAxis(LEFT_TRIGGER) > 0.5 || techStick->GetRawAxis(LEFT_TRIGGER) > 0.5)
		return ManualLoweringLift;

	if((driverStick->GetRawButton(XBOX::RBUMPER))
			&& isNewPress(indexUpTime, currentTime)){
		indexUpTime = currentTime;
		return RaisingTote;
	}
	if((driverStick->GetRawButton(XBOX::LBUMPER))
			&& isNewPress(indexDownTime, currentTime)){
		indexDownTime = currentTime;
		return LoweringTote;
	}
	if(driverStick->GetRawButton(XBOX::START)){
		return ToContainerHook;
	}
	if(driverStick->GetRawButton(XBOX::ABUTTON) || techStick->GetRawButton(XBOX::ABUTTON))// || resetLift->IsRunning())
		return ResettingLift;





	if(resetLift->IsRunning() || raiseOneTote->IsRunning() || lowerOneTote->IsRunning())
		return LiftRunning;
	if(!Robot::lift->pidController->IsEnabled()){
		return LiftStopped;
	}
	else
		return LiftRunning;
}

void Robot::TeleopPeriodic() {
	int toSend = (int)(0 + (42-0) * (Robot::lift->encoder->Get() - - 173) / (1822 - -173));
	lightPattern[0] = toSend;
	i2c->Transaction(lightPattern,1,NULL,0);
	Scheduler::GetInstance()->Run();
	logRow();
	SmartDashboard::PutBoolean("isOnTarget", Robot::lift->pidController->OnTarget());
	double time = Timer::GetFPGATimestamp();
	if(driverStick->GetRawButton(XBOX::LSTICKP) && time - driveToggleTime >= 0.5){
		driveToggleTime = time;
		Robot::drivetrain->toggleFastMode();
	}
	SmartDashboard::PutBoolean("toteDetected",lift->toteIsDetected());
	SmartDashboard::PutBoolean("In Fast Mode",Robot::drivetrain->fastMode);
	SmartDashboard::PutBoolean("In High Gear", Robot::lift->gearboxShifter->Get() == DoubleSolenoid::kForward);
	SmartDashboard::PutNumber("Hook Number ", lift->currentHookIndex);
	Robot::drivetrain->DriveTeleop(Robot::driverStick->GetX(),Robot::driverStick->GetY(),
			Robot::driverStick->GetRawAxis(4));
	if(Robot::driverStick->GetX() > .3){
//		lightPattern[1] = 9;
//		i2c->Transaction(lightPattern,1,NULL,0);
	}
	else if(Robot::driverStick->GetX() < -.3){
//		lightPattern[1] = 7;
//		i2c->Transaction(lightPattern,1,NULL,0);
	}
	else{
//		lightPattern[1] = 8;
//		i2c->Transaction(lightPattern,1,NULL,0);

	}
	LiftState liftState = getLiftState();
	switch (liftState) {
	case RaisingTote:
		resetLift->Cancel();
		stopLift->Cancel();
		raiseLift->Cancel();
		lowerLift->Cancel();
		lowerOneTote->Cancel();
//		lightPattern[0] = 1;
//		i2c->Transaction(lightPattern,1,NULL,0);
		raiseOneTote->Start();

//		lightPattern[1] = 2;
//		i2c->Transaction(lightPattern,1,NULL,0);
		break;
	case LoweringTote:
		resetLift->Cancel();
		stopLift->Cancel();
		raiseLift->Cancel();
		lowerLift->Cancel();
		raiseOneTote->Cancel();
		lowerOneTote->Start();
//		lightPattern[0] = 2;
//		i2c->Transaction(lightPattern,1,NULL,0);
//		lightPattern[1] = 3;
//		i2c->Transaction(lightPattern,1,NULL,0);
		break;
	case ManualRaisingLift:
		resetLift->Cancel();
		stopLift->Cancel();
		lowerLift->Cancel();
		raiseOneTote->Cancel();
		lowerOneTote->Cancel();
		raiseLift->Start();
//		lightPattern[0] = 1;
//		i2c->Transaction(lightPattern,1,NULL,0);
//		lightPattern[1] = 4;
//		i2c->Transaction(lightPattern,1,NULL,0);
		break;
	case ManualLoweringLift:
		resetLift->Cancel();
		stopLift->Cancel();
		raiseOneTote->Cancel();
		lowerOneTote->Cancel();
		raiseLift->Cancel();
		lowerLift->Start();
//		lightPattern[0] = 2;
//		i2c->Transaction(lightPattern,1,NULL,0);
//		lightPattern[1] = 5;
//		i2c->Transaction(lightPattern,1,NULL,0);
		break;
	case ResettingLift:
		lift->pidController->Disable();
		stopLift->Cancel();
		raiseLift->Cancel();
		lowerLift->Cancel();
		lowerOneTote->Cancel();
		raiseOneTote->Cancel();
		resetLift->Start(); //starts the command that catches the limit switch
//		lightPattern[1] = 6;
//		i2c->Transaction(lightPattern,1,NULL,0);
		break;
	case LiftStopped:
		resetLift->Cancel();
		raiseOneTote->Cancel();
		lowerOneTote->Cancel();
		raiseLift->Cancel();
		lowerLift->Cancel();
		stopLift->Start();
//		lightPattern[0] = 3;
//		i2c->Transaction(lightPattern,1,NULL,0);
//		lightPattern[1] = 7;
//		i2c->Transaction(lightPattern,1,NULL,0);
		break;
	case ToContainerHook:
		resetLift->Cancel();
		stopLift->Cancel();
		raiseLift->Cancel();
		lowerLift->Cancel();
		Robot::lift->pidController->SetSetpoint(-1789);
		break;

	default:

		;
	}
	if(techStick->GetRawButton(XBOX::YBUTTON) || driverStick->GetRawButton(XBOX::YBUTTON)){
		lift->toggleGear();
	}
	SmartDashboard::PutBoolean("resetLiftIsRunning", resetLift->IsRunning());
		if(techStick->GetRawButton(XBOX::START)){
			rotateWingsBackward->Cancel();
			rotateWingsForward->Start();
		}else if(techStick->GetRawButton(XBOX::BACK)){
			rotateWingsForward->Cancel();
			rotateWingsBackward->Start();
		}else {
			rotateWingsBackward->Cancel();
			rotateWingsForward->Cancel();
			eagleWings->wingRotater->Set(0);
		}

		if(techStick->GetRawButton(XBOX::XBUTTON)){
			eagleWings->leftWinch->Set(.4);
		}else {
			eagleWings->leftWinch->Set(0);
		}

		if(techStick->GetRawButton(XBOX::BBUTTON)){
			eagleWings->rightWinch->Set(.4);
		}else {
			eagleWings->rightWinch->Set(0);
		}
	if(techStick->GetRawButton(XBOX::RSTICKP)) {
		aligner->spinner->Set(0);
	}
//
//	if(driverStick->GetRawButton(XBOX::XBUTTON) && time - conveyorTime >= 0.5){
//		if (this->conveyorIsRunning){
//			Robot::stopConveyor->Start();
//		}
//		else {
//			Robot::runConveyor->Start();
//		}
//		conveyorIsRunning = !conveyorIsRunning;
//		conveyorTime = time;
//	}

	if(driverStick->GetRawButton(XBOX::XBUTTON)){
		Robot::runConveyor->Start();
	}
	else{
		Robot::stopConveyor->Start();
	}
	if(driverStick->GetRawButton(XBOX::BBUTTON) && time - raiseStashTime >= 0.5){
		if(this->canStasheratorUp){
			Robot::raiseStash->Run();
		}
		else{
			Robot::lowerStash->Run();
		}
		canStasheratorUp = !canStasheratorUp;
		raiseStashTime = time;
	}

	if(techStick->GetRawButton(XBOX::RBUMPER)){
		deployAligner->Start();
	}
	else if(techStick->GetRawButton(XBOX::LBUMPER)){
		retractAligner->Start();
	}
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);
