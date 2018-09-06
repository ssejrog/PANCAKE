void
test_auton() {
	flywheel_toggle = true;
	high_flag();

	auton_drive(1000, 1000);
	wait_for(&l_drive, &r_drive);

	delay(2000);

	arm_pid.des = 1800;
	wait_for(&arm_pid);
}

void
front_flag_auton() {
	flywheel_toggle = true;
	high_flag();

	//Drive Forward to ball
	auton_drive(6200,  6200);
	wait_for(&l_drive, &r_drive);
	stopTask(drive_pid_task);

	//Intake ball
	set_tank(-20, -20);
	set_ball_intake(127);
	delay(250);
	set_tank(0, 0);
	delay(600);
	set_ball_intake(0);
	set_tank(0, 0);

	//Drive Back
	auton_drive(0, 0);
	startTask(drive_pid_task);
	wait_for(&l_drive, &r_drive);

	//Turn
	auton_drive(-2200, 1850);
	wait_for(&l_drive, &r_drive);

	//Go forward to fully align with top flag
	auton_drive(1000, 4800);
	wait_for(&l_drive, &r_drive);

	//run intake a little bit
	set_ball_intake(127);
	delay(750);
	set_ball_intake(0);

	while(true){}

	//Align with middle flag
	//auton_drive(x, y);
	//
}
