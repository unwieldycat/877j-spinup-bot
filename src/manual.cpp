#include "manual.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

// ======================== Manual Control Functions ======================== //

void manual::drive_control() {
	// Variable to record robot state
	bool active = false;
	while (true) {
		// Get inputs from controller
		float turn = controller.getAnalog(okapi::ControllerAnalog::rightX);
		float drive = controller.getAnalog(okapi::ControllerAnalog::leftY);
		float strafe = controller.getAnalog(okapi::ControllerAnalog::leftX);

		// Check against deadzone
		if (-0.05 < turn > 0.05 || -0.05 < drive > 0.05 || -0.05 < strafe > 0.05) {
			// Move motors
			drive_fl.moveVelocity((drive + strafe + turn) * 200);
			drive_fr.moveVelocity((-drive + strafe + turn) * 200);
			drive_rl.moveVelocity((drive - strafe + turn) * 200);
			drive_rr.moveVelocity((-drive - strafe + turn) * 200);

			active = true;
		} else if (active == true) { // If in deadzone check if active
			// Stop all motors
			drive_fl.moveVelocity(0);
			drive_fr.moveVelocity(0);
			drive_rl.moveVelocity(0);
			drive_rr.moveVelocity(0);

			active = false;
		}

		// Wait before next loop to take load off CPU
		pros::delay(20);
	}
}

void manual::launch_control() {
	// Variable to record active state
	bool active = false;
	while (true) {
		if (controller.getDigital(okapi::ControllerDigital::A)) {
			launcher.move(127);
			active = true;
		} else if (active) {
			launcher.brake();
			active = false;
		}

		// Wait before next loop to take load off CPU
		pros::delay(20);
	}
}
