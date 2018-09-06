task
arm_pid_task() {
	while (true) {
		update_pid(&arm_pid, get_arm_sensor(), arm_pid.des);

		if (-arm_pid.motor_value <= -60) {
			arm_pid.motor_value = 60;
		}

		set_lift(-arm_pid.motor_value);

		delay(20);
	}
}

task
wrist() {
	bool flip;
	int i;
	while (true) {
		if (vexRT[Btn8U]) {
			i = flip ? 1 : -1;

			set_wrist(127*i);
			delay(450);
			set_wrist(15*i);

			flip = !flip;

			while (vexRT[Btn8U]) {
				delay(1);
			}
		}

		delay(20);
	}
}

bool
arm_down() {
	if (get_arm_sensor() >= 2000) {
		return true;
	}
	return false;
}

task
lift() {
	bool is_arm_pid;
	while (true) {
		//6U - Manual Up
		//6D - Manual Down
		//8R - Cap Post
		//8D - Fielding max height

		if (vexRT[Btn6U]) {
			stopTask(arm_pid_task);
			is_arm_pid = false;
			set_lift(127);
		}

		else if (vexRT[Btn6D]) {
			stopTask(arm_pid_task);
			is_arm_pid = false;
			set_lift(-80);
		}

		else if (vexRT[Btn8R]) {
			startTask(arm_pid_task);
			is_arm_pid = true;
			arm_pid.des = 1800;
		}

		else if (vexRT[Btn8D]) {
			startTask(arm_pid_task);
			is_arm_pid = true;
			arm_pid.des = 300;
		}

		else {
			if (is_arm_pid == false) {
				if (arm_down()) {
					set_lift(-10);
				}
				else {
					set_lift(10);
				}
			}
		}

		delay(20);
	}
}
