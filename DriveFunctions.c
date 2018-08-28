task
drive_pid_task() {
	while (true) {
		update_pid(&l_drive, get_l_drive_sensor(), l_drive.des);
		update_pid(&r_drive, get_r_drive_sensor(), r_drive.des);

		set_tank(l_drive.motor_value, r_drive.motor_value);
		delay(20);
	}
}

task
drive_control() {
	//Motor Output
	int l_output;
	int r_output;

	//Joystick Variables
	int l;
	int r;
	int threshold = 10;

	//PID Variables
	int l_target;
	int r_target;
	float kp = 0.08;

	while (true) {
		//Thresholds for joysticks
		l = abs(vexRT[Ch3]) > threshold ? vexRT[Ch3] : 0;
		r = abs(vexRT[Ch2]) > threshold ? vexRT[Ch2] : 0;

		//If joysticks are held...
		if (l != 0 || r != 0) {
			//Record currnet sensor value
			l_target = get_l_drive_sensor();
			r_target = get_r_drive_sensor();

			//Set joystick values to motors
			l_output = l;
			r_output = r;
		}
		else {
			//Hold last position
			l_output = (l_target-get_l_drive_sensor())*kp;
			r_output = (r_target-get_r_drive_sensor())*kp;
		}

		//Send motor power
		set_tank(l_output, r_output);

		delay(20);
	}
}

void
auton_drive(int l_input, int r_input) {
	l_drive.des = l_input;
	r_drive.des = r_input;
}
