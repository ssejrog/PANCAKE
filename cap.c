//Update Arm PID
task
arm_pid_task() {
	while (true) {
		update_pid(&arm_pid, get_arm_sensor(), arm_pid.des);
		set_lift(-arm_pid.motor_value);

		delay(20);
	}
}

//Manual toggle for wirst
/*
task
wrist() {
bool flip;
int i;
while (true) {
if (vexRT[Btn8U]) {
delay(50);

i = flip ? 1 : -1;

set_wrist(127*i);
delay(100);
set_wrist(127*i);
delay(100);
set_wrist(127*i);
delay(100);
set_wrist(127*i);
delay(100);
set_wrist(127*i);
delay(50);
set_wrist(15*i);

flip = !flip;

while (vexRT[Btn8U]) {
delay(1);
}
}

delay(20);
}
}
*/

static bool bflip;
void
wrist() {
	bflip = !bflip;

	int i = bflip ? 1 : -1;

	set_wrist(127*i);
	delay(100);
	set_wrist(127*i);
	delay(100);
	set_wrist(127*i);
	delay(100);
	set_wrist(127*i);
	delay(100);
	set_wrist(127*i);
	delay(50);
	set_wrist(15*i);
}

//Returns true if arm is down
bool
arm_down() {
	if (get_arm_sensor() >= INDEXER) {
		return true;
	}
	return false;
}

//Lift Task
bool is_arm_pid;
task
lift() {
	while (true) {
		//6U - Manual Up
		//6D - Manual Down
		//8R - Cap Post
		//8D - Descore Height

		//Manual Up
		if (vexRT[Btn6U]) {
			stopTask(arm_pid_task);
			is_arm_pid = false;
			set_lift(127);
		}

		//Manual Down
		else if (vexRT[Btn6D]) {
			stopTask(arm_pid_task);
			is_arm_pid = false;
			set_lift(-80);
		}

		//Cap Post
		else if (vexRT[Btn8R]) {
			startTask(arm_pid_task);
			is_arm_pid = true;
			arm_pid.des = REINTAKE_CAP;
		}

		//Descore Height
		else if (vexRT[Btn8D]) {
			startTask(arm_pid_task);
			is_arm_pid = true;
			arm_pid.des = DESCORE;
		}

		//If PID was the last thing run, run PID at last position
		//If Manual was last thing run, hold +-10 power
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
