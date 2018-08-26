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
