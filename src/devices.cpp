#include "devices.hpp"
#include "pros/adi.hpp"

// ================================ Devices ================================ //

// Inputs
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Sensors
pros::Imu inertial(9);

// Motors
pros::Motor drive_fl(1, pros::E_MOTOR_GEARSET_18, true);
pros::Motor drive_fr(2, pros::E_MOTOR_GEARSET_18);
pros::Motor drive_rl(3, pros::E_MOTOR_GEARSET_18, true);
pros::Motor drive_rr(4, pros::E_MOTOR_GEARSET_18);

pros::Motor expansion(5);
pros::Motor launcher(6, true);
pros::Motor roller(7, pros::E_MOTOR_GEARSET_36);
pros::Motor pusher(8, pros::E_MOTOR_GEARSET_36);

pros::Rotation rotation_long(11);
pros::Rotation rotation_lat(12);

// ================================= Chassis ================================= //

// Great resource on creating and tuning a PID loop
// https://smithcsrobot.weebly.com/uploads/6/0/9/5/60954939/pid_control_document.pdf

/**
 * Drive a given distance
 *
 * \param dist Distance in inches
 * \param strafe Whether to move sideways (forward is right)
 */
void drive_distance(int dist, bool strafe) {
	double error = 0;
	double error_prev = 0;
	double derivative = 0;
	double total_error = 0;

	// Proxy the rotary encoder
	pros::Rotation *rotation = (strafe) ? &rotation_lat : &rotation_long;
	rotation->reset_position();
	rotation->set_reversed(false);

	inertial.set_heading(0);
	drive_fl.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
	drive_fr.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
	drive_rl.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
	drive_rr.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);

	// Convert distance (inches) to motor rotations (degrees)
	const double end_pos = (dist / (WHEEL_DIAMETER / 2)) / (2 * PI);

	double hdg = 0;
	double hdg_error;
	double pos = 0;

	rotation->reset_position();

	while (pos < end_pos) {
		hdg = inertial.get_heading();

		// Calculate heading error
		hdg_error = (double)(hdg > 180) ? hdg_error = hdg - 360 : hdg_error = hdg;

		// Rotary encoder position
		pos = (double)rotation->get_position() / 100 / 360;

		error = pos - end_pos;           // Proportional
		total_error += error;            // Integral
		derivative = error - error_prev; // Derivative

		// Integral failsafe
		if (error == 0 || abs(error) > 40) total_error = 0;

		// Calculate motor speed and move motors
		double motor_pwr = (error * 0.5) + (total_error * 0.5) + (derivative * 0.5);
		double hdg_correction = hdg_error * 0.5;

		// Power motors
		drive_fl.move_velocity(motor_pwr - hdg_correction);
		drive_fr.move_velocity(motor_pwr + hdg_correction);
		drive_rl.move_velocity(motor_pwr - hdg_correction);
		drive_rr.move_velocity(motor_pwr + hdg_correction);

		// Assign previous error to error calculated here
		error_prev = error;
		pros::delay(20); // Rest between loops to prevent crashing
	}

	drive_fl.brake();
	drive_fr.brake();
	drive_rl.brake();
	drive_rr.brake();
}

void turn(int desired_hdg) {
	int error;
	int error_prev;
	int derivative;
	int total_error;

	inertial.set_heading(0);
	double hdg = 0;

	while (hdg < desired_hdg) {
		hdg = inertial.get_heading();

		error = hdg + desired_hdg; // Proportional
		if (error < 0) error += 360;

		total_error += error;            // Integral
		derivative = error - error_prev; // Derivative

		// Integral failsafe
		if (error == 0 || abs(error) > 40) total_error = 0;

		// Calculate motor speed and move motors
		double motor_pwr = (error * 0.5) + (total_error * 0.5) + (derivative * 0.5);
		int dir = (hdg > 180) ? -1 : 1;

		drive_fl.move_velocity(dir * -motor_pwr);
		drive_fr.move_velocity(dir * motor_pwr);
		drive_rl.move_velocity(dir * -motor_pwr);
		drive_rr.move_velocity(dir * motor_pwr);

		// Assign previous error to error calculated here
		error_prev = error;
		pros::delay(20); // Rest between loops to prevent crashing
	}

	drive_fl.brake();
	drive_fr.brake();
	drive_rl.brake();
	drive_rr.brake();
}

// ============================ Device functions ============================ //

void drive_control() {
	// Variable to record robot state
	bool active = false;

	// Direction switch stuffs
	bool dirsw_debounce = false;
	int dir = 0;

	while (true) {
		// Get inputs from controller
		float turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		float drive = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		float strafe = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

		// TODO: make this less gross
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && !dirsw_debounce) { // Front
			dir = 0;
			drive_fl.set_reversed(false);
			drive_fr.set_reversed(true);
			drive_rl.set_reversed(false);
			drive_rr.set_reversed(true);
			controller.set_text(0, 0, "Front set to Front");
			dirsw_debounce = true;
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && !dirsw_debounce) { // Right
			dir = 1;
			drive_fl.set_reversed(false);
			drive_fr.set_reversed(false);
			drive_rl.set_reversed(true);
			drive_rr.set_reversed(true);
			controller.set_text(0, 0, "Right set to Front");
			dirsw_debounce = true;
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && !dirsw_debounce) { // Back
			dir = 2;
			drive_fl.set_reversed(true);
			drive_fr.set_reversed(false);
			drive_rl.set_reversed(true);
			drive_rr.set_reversed(false);
			controller.set_text(0, 0, "Back set to Front");
			dirsw_debounce = true;
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && !dirsw_debounce) { // Left
			dir = 3;
			drive_fl.set_reversed(true);
			drive_fr.set_reversed(true);
			drive_rl.set_reversed(false);
			drive_rr.set_reversed(false);
			controller.set_text(0, 0, "Left set to Front");
			dirsw_debounce = true;
		} else {
			dirsw_debounce = false;
		}

		// Check against deadzone
		if (-0.5 < turn > 0.5 || -0.5 < drive > 0.5 || -0.5 < strafe > 0.5) {
			// Move motors
			if (dir == 0) { // Drive forward
				drive_fl.move_velocity((drive + strafe + turn) * 200);
				drive_fr.move_velocity((drive - strafe - turn) * 200);
				drive_rl.move_velocity((drive - strafe + turn) * 200);
				drive_rr.move_velocity((drive + strafe - turn) * 200);
			} else if (dir == 1) { // Drive right
				drive_fl.move_velocity((drive - strafe + turn) * 200);
				drive_fr.move_velocity((drive + strafe + turn) * 200);
				drive_rl.move_velocity((drive + strafe - turn) * 200);
				drive_rr.move_velocity((drive - strafe - turn) * 200);
			} else if (dir == 2) { // Drive backward
				drive_fl.move_velocity((drive + strafe - turn) * 200);
				drive_fr.move_velocity((drive - strafe + turn) * 200);
				drive_rl.move_velocity((drive - strafe - turn) * 200);
				drive_rr.move_velocity((drive + strafe + turn) * 200);
			} else if (dir == 3) { // Drive left
				drive_fl.move_velocity((drive - strafe - turn) * 200);
				drive_fr.move_velocity((drive + strafe - turn) * 200);
				drive_rl.move_velocity((drive + strafe + turn) * 200);
				drive_rr.move_velocity((drive - strafe + turn) * 200);
			}

			active = true;
		} else if (active == true) { // If in deadzone check if active
			// Stop all motors
			drive_fl.move_velocity(0);
			drive_fr.move_velocity(0);
			drive_rl.move_velocity(0);
			drive_rr.move_velocity(0);

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
		bool btn_a = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

		if (btn_a && !active && !debounce) {
			launcher.move(116);
			active = true;
			debounce = true;
		} else if (btn_a && active && !debounce) {
			launcher.brake();
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
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			roller.move(85);
			active = true;
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			roller.move(-85);
			active = true;
		} else if (active) {
			roller.move(0);
			active = false;
		}
	}
}

void expand_control() {
	int status = 0;
	bool active = false;
	bool debounce = false;
	while (true) {
		bool dig_x = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
		bool dig_b = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);

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
		bool dig_y = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
		if (dig_y && !debounce) {
			pusher.move_relative(360, 100);
			debounce = true;

		} else if (!dig_y && debounce) {
			debounce = false;
		}
	}
}
