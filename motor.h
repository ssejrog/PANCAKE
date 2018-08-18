#pragma systemFile

//PID
pid_ arm_pid;

//MOTOR SET
void
set_flywheel(int i_input) {
	motor[flywheel_1] =
	motor[flywheel_2] = i_input;
}

void
set_ball_intake(int i_input) {
	motor[ball_intake] = i_input;
}

void
set_wrist(int i_input) {
	motor[cap_intake] = i_input;
}

void
set_lift(int i_input) {
	motor[right_arm] =
	motor[left_arm]  = i_input;
}

void
set_tank(int i_input_l, int i_input_r) {
	motor[left_back_drive]  =
	motor[left_mid_drive]   = abs(i_input_l) > 10 ? i_input_l : 0;
	motor[right_back_drive] =
	motor[right_mid_drive]  = abs(i_input_r) > 10 ? i_input_r : 0;
}

//GET SENSOR
int
get_flywheel_sensor() {
	return SensorValue[flywheel_encoder];
}

int
get_arm_sensor() {
	return SensorValue[arm_sensor];
}

task
arm_pid_task() {
	while (true) {
		update_pid(&arm_pid, get_arm_sensor(), arm_pid.des);

		set_lift(-arm_pid.motor_value);
	}
}
