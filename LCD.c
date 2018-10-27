//Pre Auton and LCD Control
const int kMaxNumberOfPages = 5;
const int kMinNumberOfPages = 1;
int iAuton = 1;
string rgSAuton[kMaxNumberOfPages] = {"RED CAP", "RED FLAG", "BLUE CAP", "BLUE FLAG", "NONE"};

task
LCD() {
	//Strings for displaying text later
	string line_one;
	string line_two;

	//Backlight
	bLCDBacklight = true;

	while (true) {

		//DISABLED
		if (bIfiRobotDisabled) {
			if (nLCDButtons == 1) {
				iAuton = iAuton == kMinNumberOfPages ? kMaxNumberOfPages : iAuton - 1;
				wait_for_release();
			}
			if (nLCDButtons == 4) {
				iAuton = iAuton == kMaxNumberOfPages ? kMinNumberOfPages : iAuton + 1;
				wait_for_release();
			}
			line_one = "<    ------    >";
			line_two = rgSAuton[iAuton-1];
		}

		//NOT DISABLED
		else {
			line_two = "PANCAKE";
			if (bIfiAutonomousMode) {
				line_one = "AUTONOMOUS";
			} else {
				line_one = "USER CONTROL";
			}
		}

		//Display to LCD
		displayLCDCenteredString(0, line_one);
		displayLCDCenteredString( 1, line_two);
		delay(50);
		clear_lcd_lines();
	}
}
