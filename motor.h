#pragma systemFile

//PID
pid_ arm_pid;
pid_ l_drive;
pid_ r_drive;

/* MOTOR SET */
//Flywheel Set
void
set_flywheel(int i_input) {
	motor[flywheel_1] =
	motor[flywheel_2] = i_input;
}

//Ball Intaken Set
void
set_ball_intake(int i_input) {
	motor[ball_intake] = i_input;
}

//Wrist Set
void
set_wrist(int i_input) {
	motor[cap_intake] = i_input;
}

//Lift Set
void
set_lift(int i_input) {
	motor[right_arm] =
	motor[left_arm]  = i_input;
}

//Tank Set
void
set_tank(int i_input_l, int i_input_r) {
	motor[left_back_drive]  =
	motor[left_mid_drive]   = abs(i_input_l) > 10 ? i_input_l : 0;
	motor[right_back_drive] =
	motor[right_mid_drive]  = abs(i_input_r) > 10 ? i_input_r : 0;
}

/* GET SENSOR */
//Return Flywheel Sensor
int
get_flywheel_sensor() {
	return SensorValue[flywheel_encoder];
}

//Return Arm Sensor
int
get_arm_sensor() {
	return SensorValue[arm_sensor];
}

//Get Left Drive Sensor
int
get_l_drive_sensor() {
	return -SensorValue[left_drive_encoder];
}

//Get Right Drive Sensor
int
get_r_drive_sensor() {
	return -SensorValue[right_drive_encoder];
}

//Clear All Encoders
void
clear_encoder() {
	SensorValue[flywheel_encoder] =
	SensorValue[left_drive_encoder] =
	SensorValue[right_drive_encoder] = 0;
}
