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

void
set_flywheel_off() {
	for (int i = motor[flywheel_1]; i > 0; i--) {
		set_flywheel(i);
		delay(25);
	}
	set_flywheel(0);
}

task
flywheel() {
	bool PID = false;
	bool BANG = true;
	bool control_state;
	int target_velocity;
	float last_error;
	float current_error;
	bool flywheel_toggle = false;
	int flywheel_count;
	int predicted_power;
	int flywheel_output;

	const float ki = 0.2;
	const float kd = 0.5;

	while (true) {

		if (vexRT[Btn7D]) {
			flywheel_count = 1;
		}
		if (vexRT[Btn7U]) {
			flywheel_count = 2;
		}

		switch(flywheel_count) {
			case 1:
				target_velocity = 250;
				predicted_power = 30;
				break;

			case 2:
				target_velocity = 420;
				predicted_power = 90;
				break;

			default:
				break;
		}

		/* TOGGLE FLYWHEEL */
		if (vexRT[Btn7L]) {
			flywheel_toggle = !flywheel_toggle;

			while (vexRT[Btn7L]) {
				delay(1);
			}
		}

		/* FLYWHEEL CONTROLLER */
		if (flywheel_toggle) {
			last_error = current_error;
			current_error = target_velocity - velocity;

			if (velocity < (target_velocity - 25)) {
				control_state = BANG;
			}
			else if (velocity > target_velocity - 25) {
				control_state = PID;
			}

			if (control_state == BANG) {
				flywheel_output = 127;
			}
			else if (control_state == PID) {
				//flywheel_output = predicted_power + ((fkp*current_error)+(fkd*(last_error-current_error)));
				//flywheel_output = predicted_power;
				predicted_power += (ki*current_error)+(kd*(last_error-current_error));
				flywheel_output = predicted_power;
			}

			set_flywheel(flywheel_output >= 0 ? flywheel_output : 0);
			//writeDebugStreamLine("Control State:%s \nPredicted Power:%i \nCurrent Power: %i \nCurrent Velocity:%i \nTarget Velocity:%i\n", control_state ? "BANG" : "PID", predicted_power, flywheel_output, velocity, target_velocity);


			writeDebugStreamLine("%i, %i", velocity, motor[flywheel_1]);
			datalogDataGroupStart();
			datalogAddValue(0, target_velocity);
			datalogAddValue(1, velocity);
			datalogDataGroupEnd();

		}

		else {
			set_flywheel_off();
		}
		delay(20);
	}
	datalogDataGroupEnd();
}
