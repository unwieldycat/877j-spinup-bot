#include "auton.hpp"

using namespace auton;

// ============================= Skills Routine ============================= //

void auton::skills() {
	// Do roller
	drive_power(-64, 1000, true);
	roller.move(-64);
	pros::delay(500);
	roller.brake();

	// Align with next roller
	drive_distance(-24, true);
	turn(90);
	drive_distance(24, true);

	// Do roller
	drive_power(-64, 1000, true);
	roller.move(-64);
	pros::delay(500);
	roller.brake();

	// Turn to drive downfield
	drive_distance(6, true);
	drive_distance(6);
	turn(45);

	// Push discs to position
	drive_distance(5.196 * 12);
	turn(-45);
	drive_distance(24);
	drive_distance(-24);
	turn(45);

	drive_distance(2.828 * 12);
}

// ============================= Match Routines ============================= //

void do_nothing() {}

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

void roller_lg_left() {
	do_roller();
	drive_distance(3.5 * 24);
}

void roller_lg_right() {
	drive_distance(-24);
	do_roller();
	drive_distance(3.5 * 24);
}

// ============================ Routine Metadata ============================ //

std::vector<Routine> auton::routines{
    Routine(do_nothing, start_position_e::BOTH, "Do nothing"),
    Routine(lowgoal, start_position_e::BOTH, "Push discs into low goal"),
    Routine(do_roller, start_position_e::BOTH, "Do roller"),
    Routine(roller_lg_left, start_position_e::RIGHT, "Roller & Lowgoal (Left)"),
    Routine(roller_lg_right, start_position_e::LEFT, "Roller & Lowgoal (Right)")};
