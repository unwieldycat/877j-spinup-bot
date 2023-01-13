#include "devices.hpp"

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

// ================================= Chassis ================================= //

// Great resource on creating and tuning a PID loop
// https://smithcsrobot.weebly.com/uploads/6/0/9/5/60954939/pid_control_document.pdf

// FIXME: These functions should have relative movement

void drive_distance(int dist) {
	double error = 0;
	double error_prev = 0;
	double derivative = 0;
	double total_error = 0;

	drive_fl.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
	drive_fr.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
	drive_rl.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
	drive_rr.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);

	// Convert distance (feet) to motor rotations (degrees)

	const double end_pos = (0.7071067812 * dist / (WHEEL_DIAMETER / 2)) / (2 * PI);
	double avg_pos = 0;

	drive_fl.set_zero_position(drive_fl.get_position());
	drive_fr.set_zero_position(drive_fl.get_position());
	drive_rl.set_zero_position(drive_fl.get_position());
	drive_rr.set_zero_position(drive_fl.get_position());

	std::cout << end_pos << std::endl;

	while (avg_pos < end_pos) {
		// Average motor positions
		avg_pos = -(drive_fl.get_position() + drive_fr.get_position() + drive_rl.get_position() +
		            drive_rr.get_position()) /
		          4;

		error = avg_pos - end_pos;       // Proportional
		total_error += error;            // Integral
		derivative = error - error_prev; // Derivative

		// Integral failsafe
		if (error == 0 || abs(error) > 40) total_error = 0;

		// Calculate motor speed and move motors
		double motor_pwr = (error * 10) + (total_error * 10) + (derivative * 10);

		drive_fl.move_velocity(motor_pwr);
		drive_fr.move_velocity(motor_pwr);
		drive_rl.move_velocity(motor_pwr);
		drive_rr.move_velocity(motor_pwr);

		// Assign previous error to error calculated here
		error_prev = error;
		pros::delay(20); // Rest between loops to prevent crashing
	}
}

void turn(int desired_hdg) {
	int error;
	int error_prev;
	int derivative;
	int total_error;

	int hdg_current = 0;

	while (hdg_current < desired_hdg) {
		// Average motor positions
		hdg_current = inertial.get_heading();

		error = hdg_current - desired_hdg; // Proportional
		total_error += error;              // Integral
		derivative = error - error_prev;   // Derivative

		// Integral failsafe
		if (error == 0 || abs(error) > 40) total_error = 0;

		// Calculate motor speed and move motors
		double motor_pwr = (error * 1) + (total_error * 1) + (derivative * 1);

		drive_fl.move_velocity(motor_pwr);
		drive_fr.move_velocity(motor_pwr);
		drive_rl.move_velocity(motor_pwr);
		drive_rr.move_velocity(motor_pwr);

		// Assign previous error to error calculated here
		error_prev = error;
		pros::delay(20); // Rest between loops to prevent crashing
	}
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
