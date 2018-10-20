//Calculate flywheel velocity per 80ms
float velocity;
task
flywheel_rpm_task() {
	int last_value, current_value;
	while (true) {
		last_value = abs(get_flywheel_sensor());
		delay(80);
		current_value = abs(get_flywheel_sensor());
		velocity = current_value - last_value;
		SensorValue[flywheel_encoder] = 0;
	}
}

//Ramp the flywheel down when during it off
void
set_flywheel_off() {
	for (int i = motor[flywheel_1]; i > 0; i--) {
		set_flywheel(i);
		delay(25);
	}
	set_flywheel(0);
}

//Set flywheel speeds
int target_velocity;
int predicted_power;
void
high_flag() {
	target_velocity = 420;
	predicted_power = 100;
}

//Flywheel logic
bool flywheel_graph;
bool flywheel_toggle = false;
task
flywheel() {
	bool PID = false;
	bool BANG = true;
	bool control_state;
	float last_error;
	float current_error;
	int flywheel_output;

	const float ki = 0.04;
	const float kd = 0.5;

	//Default the speed to high flag (because this is the main speed)
	high_flag();

	while (true) {

		//Flywheel Controller
		if (flywheel_toggle) {
			last_error = current_error;
			current_error = target_velocity - velocity;

			//Fliping Control States between BANG and PID
			if (velocity < (target_velocity - 5)) {
				control_state = BANG;
			}
			else if (velocity > (target_velocity - 5)) {
				control_state = PID;
			}

			//Run 127 power if Bang
			if (control_state == BANG) {
				flywheel_output = 127;
			}
			//Run ID loop if PID
			else if (control_state == PID) {
				predicted_power += (ki*current_error)+(kd*(last_error-current_error));
				flywheel_output = predicted_power;
			}

			set_flywheel(flywheel_output >= 0 ? flywheel_output : 0);

			//Graph flywheel velocity
			if (flywheel_graph) {
				writeDebugStreamLine("%i, %i", velocity, motor[flywheel_1]);
				datalogDataGroupStart();
				datalogAddValue(0, target_velocity);
				datalogAddValue(1, velocity);
				datalogDataGroupEnd();
			}
			//Output debugger window
			else {
				writeDebugStreamLine("Control State:%s", control_state ? "BANG" : "PID");
				writeDebugStreamLine("Predicted Power:%i", predicted_power);
				writeDebugStreamLine("Current Power:%i", flywheel_output);
				writeDebugStreamLine("Current Velocity:%i", velocity);
				writeDebugStreamLine("Target Velocity:%i", target_velocity);
				writeDebugStreamLine("\n");
			}

		}

		else {
			if (motor[flywheel_1] > 0) {
				set_flywheel_off();
			}
		}
		delay(20);
	}
}

void
indexer() {
	arm_pid.des = INDEXER;
	delay(250);

	set_ball_intake(127);
	delay(200);
	set_ball_intake(0);

	arm_pid.des = ARM_DOWN;
}

task
ball_intake_task() {
	while (true) {
		if (vexRT[Btn5D]) {
			set_ball_intake(127);
		}
		else if (vexRT[Btn5U]) {
			stopTask(lift);
			startTask(arm_pid_task);
			is_arm_pid = true;

			arm_pid.des = INDEXER;
			delay(250);

			set_ball_intake(127);
			delay(200);

			while (vexRT[Btn5U]) {
				set_ball_intake(50);
				delay(20);
			}
			set_ball_intake(0);

			arm_pid.des = ARM_DOWN;

			startTask(lift);
		}
		else if (vexRT[Btn7D]) {
			set_ball_intake(-127);
		}
		else {
			set_ball_intake(0);
		}
	}
}
