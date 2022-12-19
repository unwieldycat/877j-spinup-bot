#include "devices.hpp"
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

pros::Motor expansion(5);
pros::Motor launcher(6, true);
pros::Motor intake(7, pros::motor_gearset_e_t::E_MOTOR_GEARSET_36);
pros::Motor pusher(8, pros::motor_gearset_e_t::E_MOTOR_GEARSET_36);

// Chassis
std::shared_ptr<okapi::OdomChassisController> chassis =
    okapi::ChassisControllerBuilder()
        .withMotors(drive_fl, drive_fr, drive_rr, drive_rl)
        .withDimensions(okapi::AbstractMotor::gearset::green, {{4_in, 13_in}, okapi::imev5GreenTPR})
        .withOdometry()
        .buildOdometry();

// ============================ Device functions ============================ //

void auto_roller() {
	// FIXME: Just doesnt work properly 👍
	while (distance.get() < 50) {
		int hue = optical.get_hue();

		intake.move(127);
		pros::delay(1000);

		// If the optical sensor detects red then blue is
		// selected and vice versa
		if ((hue < 10 || hue > 350) && team == team_e::TEAM_BLUE ||
		    (hue < 260 && hue > 190) && team == team_e::TEAM_RED) {
			intake.brake();
			break;
		}
	}
}

void drive_control() {
	// Variable to record robot state
	bool active = false;

	// Direction switch stuffs
	bool dirsw_debounce = false;
	int dir = 0;

	while (true) {
		// Get inputs from controller
		float turn = controller.getAnalog(okapi::ControllerAnalog::rightX);
		float drive = controller.getAnalog(okapi::ControllerAnalog::leftY);
		float strafe = controller.getAnalog(okapi::ControllerAnalog::leftX);

		// TODO: make this less gross
		if (controller.getDigital(okapi::ControllerDigital::up) && !dirsw_debounce) { // Front
			dir = 0;
			controller.setText(0, 0, "Front set to Front");
			dirsw_debounce = true;
		} else if (controller.getDigital(okapi::ControllerDigital::right) && !dirsw_debounce) { // Right
			dir = 1;
			controller.setText(0, 0, "Right set to Front");
			dirsw_debounce = true;
		} else if (controller.getDigital(okapi::ControllerDigital::down) && !dirsw_debounce) { // Back
			dir = 2;
			controller.setText(0, 0, "Back set to Front");
			dirsw_debounce = true;
		} else if (controller.getDigital(okapi::ControllerDigital::left) && !dirsw_debounce) { // Left
			dir = 3;
			controller.setText(0, 0, "Left set to Front");
			dirsw_debounce = true;
		} else {
			dirsw_debounce = false;
		}

		// Check against deadzone
		if (-0.5 < turn > 0.5 || -0.5 < drive > 0.5 || -0.5 < strafe > 0.5) {
			// Move motors
			if (dir == 0) { // Drive forward
				drive_fl.moveVelocity((drive + strafe + turn) * 200);
				drive_fr.moveVelocity((-drive + strafe + turn) * 200);
				drive_rl.moveVelocity((drive - strafe + turn) * 200);
				drive_rr.moveVelocity((-drive - strafe + turn) * 200);
			} else if (dir == 1) { // Drive right
				drive_fl.moveVelocity((drive - strafe + turn) * 200);
				drive_fr.moveVelocity((drive + strafe + turn) * 200);
				drive_rl.moveVelocity((-drive - strafe + turn) * 200);
				drive_rr.moveVelocity((-drive + strafe + turn) * 200);
			} else if (dir == 2) { // Drive backward
				drive_fl.moveVelocity((-drive - strafe + turn) * 200);
				drive_fr.moveVelocity((drive - strafe + turn) * 200);
				drive_rl.moveVelocity((-drive + strafe + turn) * 200);
				drive_rr.moveVelocity((drive + strafe + turn) * 200);
			} else if (dir == 3) { // Drive left
				drive_fl.moveVelocity((-drive + strafe + turn) * 200);
				drive_fr.moveVelocity((-drive - strafe + turn) * 200);
				drive_rl.moveVelocity((drive + strafe + turn) * 200);
				drive_rr.moveVelocity((drive - strafe + turn) * 200);
			}

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

void launch_control() {
	// Variable to record active state
	bool active = false;
	bool debounce = false;
	while (true) {
		bool btn_a = controller.getDigital(okapi::ControllerDigital::A);

		if (btn_a && !active && !debounce) {
			launcher.move(116);
			debounce = true;
			active = true;
			debounce = true;
		} else if (btn_a && active && !debounce) {
			launcher.brake();
			debounce = true;
			active = false;
			debounce = true;
		} else if (!btn_a && debounce) {
			debounce = false;
		}
		// Wait before next loop to take load off CPU
		pros::delay(20);
	}
}

void roller_control() {
	bool active = false;
	while (true) {
		if (controller.getDigital(okapi::ControllerDigital::L1)) {
			intake.move(127);
			active = true;
		} else if (controller.getDigital(okapi::ControllerDigital::L2)) {
			intake.move(-127);
			active = true;
		} else if (active) {
			intake.move(0);
			active = false;
		}
	}
}

void expand_control() {
	int status = 0;
	bool active = false;
	bool debounce = false;
	while (true) {
		bool dig_x = controller.getDigital(okapi::ControllerDigital::X);
		bool dig_b = controller.getDigital(okapi::ControllerDigital::B);

		if (dig_x && status < 1 && !debounce) {
			debounce = true;
			status++;
		} else if (dig_b && status > -1 && !debounce) {
			debounce = true;
			status--;
		} else if (!dig_x && !dig_b && debounce) {
			debounce = false;
		}

		if (status == 0 && active == true) {
			expansion.move(0);
			active = false;
		} else if (status == -1 && active == false) {
			expansion.move(-96);
			active = true;
		} else if (status == 1 && active == false) {
			expansion.move(96);
			active = true;
		}
	}
}

void manual_push() {
	bool debounce = false;
	pusher.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	while (true) {
		bool dig_y = controller.getDigital(okapi::ControllerDigital::Y);
		if (dig_y && !debounce) {
			pusher.move_relative(360, 100);
			debounce = true;

		} else if (!dig_y && debounce) {
			debounce = false;
		}
	}
}
