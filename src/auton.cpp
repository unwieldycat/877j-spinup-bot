#include "auton.hpp"

using namespace auton;

// ============================= Skills Routine ============================= //

void auton::skills() {}

// ============================= Match Routines ============================= //

/**
 * Win point routine
 */
void solo_awp() {}

/**
 * Only do closest roller and then move out way
 */
void one_roller_close() {}

/**
 * Do both rollers and ignore discs
 */
void both_rollers_infront() {
	auto_roller();
	chassis->turnToAngle(-45_deg);
	chassis->moveDistance(-7_ft);
	chassis->turnToAngle(-90_deg);
	auto_roller();
}

void both_rollers_notinfront() {}

// ============================ Routine Metadata ============================ //

std::vector<Routine> auton::routines{
    Routine(solo_awp, start_position_e::LEFT, "Solo Autonomous Win Point"),
    Routine(one_roller_close, start_position_e::BOTH, "Set One Roller"),
    Routine(both_rollers_infront, start_position_e::LEFT, "Set Both Rollers"),
    Routine(both_rollers_notinfront, start_position_e::RIGHT, "Set Both Rollers")};
