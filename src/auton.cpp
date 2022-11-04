#include "auton.hpp"

using namespace auton;

// ============================= Skills Routine ============================= //

void auton::skills() {}

// ============================= Match Routines ============================= //

/**
 * Do the left side roller
 */
void left_roller() {
	chassis->moveDistance(-0.5_ft);
	auto_roller();
}

/**
 * Do the right side roller
 */
void right_roller() {
	chassis->turnAngle(-90_deg);
	chassis->moveDistance(2_ft);
	chassis->turnAngle(90_deg);
	chassis->moveDistance(-0.5_ft);
	auto_roller();
}

// ============================ Routine Metadata ============================ //

std::vector<Routine> auton::routines{
    Routine(left_roller, start_position_e::LEFT, "Do left side roller (Start on same tile)"),
    Routine(right_roller, start_position_e::RIGHT, "Do right side roller (Start on closest tile)")};
