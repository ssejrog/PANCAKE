///////
// OLD BOI AUTONS
///////

/*
//Intake Ball under Cap
void
intake_ball_auton() {
flywheel_toggle = true;
high_flag();

//Drive Forward to ball
drive_pid_lim = 50;
auton_drive(5250,  5250);
wait_for(&l_drive, &r_drive);
stopTask(drive_pid_task);
drive_pid_lim = 70;

//Intake ball
set_tank(20, 20);
set_ball_intake(127);
delay(1000);
set_tank(00, 00);
//delay(250);
set_ball_intake(0);
set_tank(0, 0);
//850

//Drive Back
auton_drive(-400, -400);
startTask(drive_pid_task);
wait_for(&l_drive, &r_drive);
delay(350);
}

//Ideally, intake ball under cap and score all 3 flags
void
flag_auton() {
intake_ball_auton();

//Turn
drive_pid_lim = 127;
auton_drive(-2100, 1800);
wait_for(&l_drive, &r_drive);
delay(350);
drive_pid_lim = 70;

//Go forward to fully align with top flag
auton_drive(1100, 4600); //4900
wait_for(&l_drive, &r_drive);
delay(250);

//run intake a little bit
set_ball_intake(127);
delay(850);
set_ball_intake(0);
delay(350);


//Align with middle flag
auton_drive(3000, 6300);
wait_for(&l_drive, &r_drive);
delay(250);

//Score last ball
set_ball_intake(127);
delay(850);
set_ball_intake(0);
delay(350);

//Turn
drive_pid_lim = 127;
auton_drive(4000,7300);
//wait_for(&l_drive, &r_drive);
delay(1000);
drive_pid_lim = 70;

//hit bottom flag
auton_drive(5000, 9300);
wait_for(&l_drive, &r_drive);
}
*/

//Intake ball under cap
void
intake_ball_auton() {
	//Turn flywheel on
	flywheel_toggle = true;
	drive_constants();

	//Turn intake on
	set_ball_intake(127);

	//Go forward about 90% of the way
	auton_drive(1100, 1100);
	wait_for(&l_drive, &r_drive);

	//Limit drive to half power
	drive_pid_lim = 50;
	delay(250);

	//Drive forward a bit more and intake ball
	auton_drive(1650, 1650);
	wait_for(&l_drive, &r_drive);
	delay(250);

	//Limit drive to full speed
	drive_pid_lim = 127;

	//Drive back to 0, 0
	auton_drive(0, 0);
	wait_for(&l_drive, &r_drive);
	set_ball_intake(0);
	delay(250);
}

void
flag_auton() {
	high_flag();
	intake_ball_auton();
	//Turn to face flag
	turn_constants();
	auton_drive(-385, 385);
	wait_for(&l_drive, &r_drive);
	delay(1500);

	//Go to shooting position
	drive_constants();
	//auton_drive(65, 835);
	auton_drive(-100, 705);
	wait_for(&l_drive, &r_drive);
	delay(400);

	//SHOOT!
	indexer();
	delay(500);


	//Go to shooting position
	//auton_drive(750, 1605);
	//auton_drive(750, 1555);
	//auton_drive(725, 1530);
	//auton_drive(700, 1505);
	auton_drive(710, 1505);
	set_ball_intake(127);
	wait_for(&l_drive, &r_drive);
	delay(400);
	set_ball_intake(0);

	//SHOOT!
	indexer();
	delay(500);


	//Turn to hit bottom flag
	turn_constants();
	auton_drive(680, 1670);
	wait_for(&l_drive, &r_drive);
	delay(500);

	//Hit bottom flag
	drive_constants();
	auton_drive(1300, 2250);
	wait_for(&l_drive, &r_drive);
	delay(200);
	//Turn
	//wait_for(&l_drive, &r_drive);

	//Go forward and shoot high flag
	//wait_for(&l_drive, &r_drive);

	//Shoot ball
	//indexer();

	//Go forward and shoot middle flag
	//wait_for(&l_drive, &r_drive);

	//Shoot ball
	//indexer();

	//Turn
	//wait_for(&l_drive, &r_drive);

	//Go forward and hit bottom flag
	//wait_for(&l_drive, &r_drive);

}

void
back_ball_auton() {
	auton_mid_flag();
	intake_ball_auton();

	//Turn to face flag
	turn_constants_two();
	auton_drive(-288, 292);
	wait_for(&l_drive, &r_drive);
	set_ball_intake(0);
	delay(5000);

	////Turn to face flag
	//turn_constants();
	//auton_drive(1650-370, 1650+385);
	//wait_for(&l_drive, &r_drive);
	//delay(1500);
	//set_ball_intake(0);

	//SHOOT
	indexer();
	delay(500);

	//RAMP UP FLYWHEEL
	auton_top_flag();
	set_ball_intake(127);
	delay(1500);
	set_ball_intake(0);

	//SHOOT
	indexer();
	delay(500);
	//*/
}
