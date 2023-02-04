#include "auton.hpp"

using namespace auton;

// ============================= Skills Routine ============================= //

void auton::skills() {
	// Do roller
	drive_power(-64, 1000, true);
	roller.move(-64);
	pros::delay(200);
	roller.brake();

	// Align with next roller
	drive_distance(-24 * 2, true);
	turn(90);
	drive_distance(24, true);
	drive_distance(-24);

	// Do roller
	drive_power(-64, 1000, true);
	roller.move(-64);
	pros::delay(200);
	roller.brake();

	// Turn to point downfield
	drive_distance(-12, true);
	turn(45);

	controller.rumble("-");
	pros::delay(2000);

	expansion.move(-127);
	pros::delay(3000);
	expansion.brake();
}

// ============================= Match Routines ============================= //

auton::action_t auton::do_nothing() { return 0; }

/**
 * Only push discs into low goal
 */
void lowgoal() {
	drive_power(64, 2000);
	drive_power(-64, 2000);
}

void do_roller() {
	drive_power(-64, 1000, true);

	roller.move(-64);
	pros::delay(180);
	roller.brake();

	drive_power(64, 250, true);
}

void roller_left() { do_roller(); }

void roller_right() {
	drive_distance(24);
	do_roller();
}

// ============================ Routine Metadata ============================ //

std::vector<Routine> auton::routines{
    Routine(do_nothing, start_position_e::BOTH, "Do nothing"),
    Routine(lowgoal, start_position_e::BOTH, "Push discs into low goal"),
    Routine(do_roller, start_position_e::BOTH, "Do roller"),
    Routine(roller_left, start_position_e::RIGHT, "Roller (Left)"),
    Routine(roller_right, start_position_e::LEFT, "Roller (Right)")};
