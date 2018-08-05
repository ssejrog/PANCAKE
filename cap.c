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

task
lift() {
	//bool b_lift;
	//startTask(pid_hold);
	while (true) {
		//if (vexRT[Btn6U]) {
		//	arm_pid.f_des = b_lift ? 2000 : 3000;
		//	wait_for(&arm_pid);
		//	b_lift = !b_lift;

		//	while(vexRT[Btn6U]) {
		//		delay(1);
		//	}
		//}

		//set_lift(vexRT[Btn6U]?127:(vexRT[Btn6D]?-80:10));

		if (vexRT[Btn6U]) {
			set_lift(127);
		}
		else if (vexRT[Btn6D]) {
			set_lift(-80);
		}
		else {
			if (get_arm_sensor() >= 2000) {
				set_lift(-10);
			}
			else {
				set_lift(10);
			}
		}

		delay(20);
	}
}
