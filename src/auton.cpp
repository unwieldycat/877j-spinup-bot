#include "auton.hpp"

using namespace auton;

// ============================= Skills Routine ============================= //

void auton::skills() {}

// ============================= Match Routines ============================= //

/**
 * For when our alliance partner has an infinitely better routine
 */
void do_nothing() {}

/**
 * Only push discs into low goal
 */
void lowgoal() {
	drive_power(64, 2000);
	drive_power(-64, 2000);
}

// TODO: Simple roller routines
void one_roller_left() {
	drive_power(-64, 1000, true);

	roller.move(-64);
	pros::delay(250);
	roller.brake();

	drive_power(64, 250, true);
}

void one_roller_right() {}

// ============================ Routine Metadata ============================ //

std::vector<Routine> auton::routines{
    Routine(do_nothing, start_position_e::BOTH, "Do nothing"),
    Routine(lowgoal, start_position_e::BOTH, "Push discs into low goal"),
    Routine(one_roller_right, start_position_e::RIGHT, "Set One Roller (Right)"),
    Routine(one_roller_left, start_position_e::LEFT, "Set One Roller (Left)")};
