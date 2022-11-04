#include "devices.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "pros/distance.hpp"

// ================================ Devices ================================ //

// Inputs
okapi::Controller controller(okapi::ControllerId::master);

// Sensors
pros::Distance distance(9);
pros::Optical optical(10);

// Motors
okapi::Motor drive_fl(1);
okapi::Motor drive_fr(2);
okapi::Motor drive_rl(3);
okapi::Motor drive_rr(4);

pros::Motor roller(5);
pros::Motor expansion_l(11);
pros::Motor expansion_r(12);

// Chassis
std::shared_ptr<okapi::OdomChassisController> chassis =
    okapi::ChassisControllerBuilder()
        .withMotors(drive_fl, drive_fr, drive_rr, drive_rl)
        .withDimensions(
            okapi::AbstractMotor::gearset::green, {{4_in, 11.5_in}, okapi::imev5GreenTPR}
        )
        .withOdometry()
        .buildOdometry();

// ============================ Device functions ============================ //

void auto_roller() {
	// FIXME: Just doesnt work properly 👍
	bool done = false;
	team = team_e::TEAM_RED;
	while (!done) {
		if (distance.get() > 100) done = true;
		int hue = optical.get_hue();

		roller.move(64);
		pros::delay(500);

		// If the optical sensor detects red then blue is
		// selected and vice versa
		if ((hue < 10 || hue > 350) && team == team_e::TEAM_BLUE ||
		    (hue < 260 || hue > 190) && team == team_e::TEAM_RED) {
			roller.brake();
			done = true;
		}
	}
}

void roller_control() {
	bool active = false;
	while (true) {
		bool foward = controller.getDigital(okapi::ControllerDigital::L1);
		bool back = controller.getDigital(okapi::ControllerDigital::L2);

		if (foward) {
			roller.move(127);
			active = true;
		} else if (back) {
			roller.move(-127);
			active = true;
		} else if (active) {
			roller.brake();
			active = false;
		}
	}
}

void drive_control() {
	// Variable to record robot state
	bool active = false;
	while (true) {
		// Get inputs from controller
		float turn = controller.getAnalog(okapi::ControllerAnalog::rightX);
		float drive = controller.getAnalog(okapi::ControllerAnalog::leftY);

		// Check against deadzone
		if (-0.05 < turn > 0.05 || -0.05 < drive > 0.05) {
			// Move motors
			drive_fl.moveVelocity((drive + turn) * 200);
			drive_fr.moveVelocity((-drive + turn) * 200);
			drive_rl.moveVelocity((drive + turn) * 200);
			drive_rr.moveVelocity((-drive + turn) * 200);

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

void expand_control() {
	while (true) {
		if (controller.getDigital(okapi::ControllerDigital::B)) {
			expansion_l.move(127);
			expansion_r.move(127);
		}
	}
}
