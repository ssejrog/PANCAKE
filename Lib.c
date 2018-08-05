#pragma systemFile

typedef struct {
	float f_current;
	float k_p;
	float f_integral;
	float k_d;
	float k_i;
	float f_des;
	float f_error;
	float f_der;
	float f_lasterror;
	float f_threshold;
	int time;
	int i_motor_value;
} pid_;

void
pid_init(pid_ *this, float kp, float ki, float kd) {
	this->k_p = kp;
	this->k_i = ki;
	this->k_d = kd;
}

void
update_pid(pid_ *this, float f_current, float f_setpoint) {
	this->time = nSysTime;
	long dt = nSysTime - this->time;
	if (dt == 0) {
		dt = 1;
	}

	float error = (f_setpoint - f_current) / dt;

	this->f_integral = error * dt;

	float derivative = (dt == 0) ? 0.0 : ((error - this->f_error) / dt);

	this->i_motor_value = (this->f_error*this->k_p)+(this->f_integral*this->k_i)+(this->f_der*this->k_d);

	this->f_error = error;
}

void
wait_for(pid_ *this) {
	while (true) {
		delay(20);
		if (abs(this->f_error) < 20) {
			return;
		}
	}
}
