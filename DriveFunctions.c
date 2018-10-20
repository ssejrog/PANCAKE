void
turn_constants() {
	pid_init(&l_drive, 0.7, 0.0002, 18);
	pid_init(&r_drive, 0.7, 0.0002, 18);
}

void
drive_constants() {
	pid_init(&l_drive, 0.3, 0.00013, 25);
	pid_init(&r_drive, 0.3, 0.00013, 25);
}

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

int tsArray[128] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	20, 21, 21, 21, 22, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127
};

int
trueSpeed(int input) {
	input = abs(input) > 127 ? sgn(input)*127 : input;

	return sgn(input) * tsArray[abs(input)];
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
	float kp = 0.1;

	while (true) {
		//Thresholds for joysticks
		l = abs(vexRT[Ch3]) > threshold ? trueSpeed(vexRT[Ch3]) : 0;
		r = abs(vexRT[Ch2]) > threshold ? trueSpeed(vexRT[Ch2]) : 0;

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
