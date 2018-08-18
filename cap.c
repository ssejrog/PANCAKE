task
wrist() {
	bool b_flip;
	while (true) {
		if (vexRT[Btn8U]) {
			if (b_flip) {
				set_wrist(127);
				delay(450);
				set_wrist(15);
			} else {
				set_wrist(-127);
				delay(450);
				set_wrist(-15);
			}

			b_flip = !b_flip;

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

bool is_arm_pid;
task
lift() {
	//bool b_lift;
	//startTask(pid_hold);
	while (true) {
		//6U - Manual Up
		//6D - Manual DOwn
		//8R - Cap Post
		//8D - Fielding

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
			arm_pid.des = 250;
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

		//if (vexRT[Btn6U]) {
		//	set_lift(127);
		//}
		//else if (vexRT[Btn6D]) {
		//	if (arm_down()) {
		//		set_lift(1);
		//	}
		//	else {
		//		set_lift(-80);
		//	}
		//}
		//else {
		//	if (arm_down()) {
		//		set_lift(-10);
		//	}
		//	else {
		//		set_lift(10);
		//	}
		//}

		delay(20);
	}
}
