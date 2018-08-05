#pragma systemFile

typedef struct {
	float current;
	float kp;
	float integral;
	float kd;
	float ki;
	float des;
	float error;
	float der;
	float lasterror;
	float threshold;
	int time;
	int motor_value;
} pid_;

void
pid_init(pid_ *this, float p, float i, float d) {
	this->kp = p;
	this->ki = i;
	this->kd = d;
}

void
update_pid(pid_ *this, float current, float setpoint) {
	long dt = nSysTime-this->time;
	float error = (setpoint-current)/dt;
	float derivative = (dt==0) ? 0.0 : ((error-this->error)/dt);

	this->motor_value = (this->error*this->kp)+(this->integral*this->ki)+(this->der*this->kd);

	this->error = error;
	this->time = nSysTime;
}

void
wait_for(pid_ *this) {
	while (true) {
		delay(20);
		if (abs(this->error) < 20) {
			return;
		}
	}
}
