//void
//test_auton() {
//	flywheel_toggle = true;
//	high_flag();

//	auton_drive(1000, 1000);
//	wait_for(&l_drive, &r_drive);

//	delay(2000);

//	arm_pid.des = 1800;
//	wait_for(&arm_pid);
//}

//Intake Ball under Cap
void
intake_ball_auton() {
	flywheel_toggle = true;
	high_flag();

	//Drive Forward to ball
	drive_pid_lim = 50;
	auton_drive(5250,  5250);
	wait_for(&l_drive, &r_drive);
	stopTask(drive_pid_task);
	drive_pid_lim = 70;

	//Intake ball
	set_tank(20, 20);
	set_ball_intake(127);
	delay(1000);
	set_tank(00, 00);
	//delay(250);
	set_ball_intake(0);
	set_tank(0, 0);
	//850

	//Drive Back
	auton_drive(-400, -400);
	startTask(drive_pid_task);
	wait_for(&l_drive, &r_drive);
	delay(350);
}

void
flag_auton() {
	/*
	flywheel_toggle = true;
	high_flag();

	//Drive Forward to ball
	drive_pid_lim = 50;
	auton_drive(5250,  5250);
	wait_for(&l_drive, &r_drive);
	stopTask(drive_pid_task);
	drive_pid_lim = 70;

	//Intake ball
	set_tank(20, 20);
	set_ball_intake(127);
	delay(1000);
	set_tank(00, 00);
	//delay(250);
	set_ball_intake(0);
	set_tank(0, 0);
	//850

	//Drive Back
	auton_drive(-400, -400);
	startTask(drive_pid_task);
	wait_for(&l_drive, &r_drive);
	delay(350);
	*/

	//Turn
	drive_pid_lim = 127;
	auton_drive(-2100, 1800);
	wait_for(&l_drive, &r_drive);
	delay(350);
	drive_pid_lim = 70;

	//Go forward to fully align with top flag
	auton_drive(1100, 4600); //4900
	wait_for(&l_drive, &r_drive);
	delay(250);

	//run intake a little bit
	set_ball_intake(127);
	delay(850);
	set_ball_intake(0);
	delay(350);


	//Align with middle flag
	auton_drive(3000, 6300);
	wait_for(&l_drive, &r_drive);
	delay(250);

	//Score last ball
	set_ball_intake(127);
	delay(850);
	set_ball_intake(0);
	delay(350);

	//Turn
	drive_pid_lim = 127;
	auton_drive(3000,7300);
	wait_for(&l_drive, &r_drive);
	drive_pid_lim = 70;

	//hit bottom flag
	auton_drive(5000, 9300);
	wait_for(&l_drive, &r_drive);
}
