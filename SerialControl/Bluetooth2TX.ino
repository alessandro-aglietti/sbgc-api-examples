#include <inttypes.h>
#include <SBGC.h>
#include <SBGC_Arduino.h>


// Serial baud rate should match with the rate, configured for the SimpleBGC controller
#define SERIAL_SPEED 115200

// delay between commands, ms
#define SBGC_CMD_DELAY 20

/*****************************************************************************/

HardwareSerial &serial = Serial;

void setup() {
	serial.begin(SERIAL_SPEED);
	SBGC_Demo_setup(&serial);

	// Take a pause to let gimbal controller to initialize
	delay(3000);
}


void loop() {
	SBGC_cmd_control_t c = { 0, 0, 0, 0, 0, 0, 0 };

	// Move camera to initial position (all angles are zero)
	// Set speed 30 degree/sec
	c.mode = SBGC_CONTROL_MODE_ANGLE;
	c.speedROLL = c.speedPITCH = c.speedYAW = 30 * SBGC_SPEED_SCALE;
	SBGC_cmd_control_send(c, sbgc_parser);
	delay(3000);
	
	blink_led(1);
	/////////////////// Demo 1. PITCH and YAW gimbal by 40 and 30 degrees both sides and return back.
	// Actual speed depends on PID setting.
	// Whait 5 sec to finish
	c.mode = SBGC_CONTROL_MODE_ANGLE;
	c.anglePITCH = SBGC_DEGREE_TO_ANGLE(40);
	c.angleROLL = SBGC_DEGREE_TO_ANGLE(30);
	SBGC_cmd_control_send(c, sbgc_parser);
	delay(4000);
}
