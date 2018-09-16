int drive_pid_lim = 127;
task
drive_pid_task() {
	while (true) {
		update_pid(&l_drive, get_l_drive_sensor(), l_drive.des);
		update_pid(&r_drive, get_r_drive_sensor(), r_drive.des);

		set_tank(clipNum(l_drive.motor_value, drive_pid_lim), clipNum(r_drive.motor_value, drive_pid_lim));
		delay(20);
	}
}

//Active Brake and Manual Control
task
drive_control() {
	//Motor Output
	int l_output = 0;
	int r_output = 0;

	//Joystick Variables
	int l = 0;
	int r = 0;
	int threshold = 10;

	//PID Variables
	int l_target = 0;
	int r_target = 0;
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

//"bFlip" sets the left parameter to the right, making the robot turn the opposite direction
bool bFlip = false;
//Void for making it easier to set drive target values
void
auton_drive(int l_input, int r_input) {
	if (!bFlip) {
		l_drive.des = l_input;
		r_drive.des = r_input;
	} else {
		l_drive.des = r_input;
		r_drive.des = l_input;
	}
}
