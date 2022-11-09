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
void preload() { chassis->driveToPoint({2_ft, 0_ft}); }

void one_roller_right() {}

/**
 * Do both rollers and ignore discs
 */
void both_rollers_right() {
	auto_roller();
	chassis->driveToPoint({-5_ft, -5_ft});
	chassis->turnToAngle(-90_deg);
	chassis->driveToPoint({-11_ft, -11_ft});
	auto_roller();
}

void both_rollers_left() {
	chassis->driveToPoint({-1.5_ft, 0_ft});
	auto_roller();
	chassis->driveToPoint({5_ft, 5_ft});
	chassis->driveToPoint({11_ft, 11_ft});
	chassis->turnToAngle(90_deg);
	auto_roller();
}

void awp_left() {}

void awp_right() {
	launcher.move(127);
	auto_roller();
	chassis->driveToPoint({-5.5_ft, -5.5_ft});
	chassis->turnToAngle(135_deg);
}

// ============================ Routine Metadata ============================ //

std::vector<Routine> auton::routines{
    Routine(solo_awp, start_position_e::LEFT, "Solo Autonomous Win Point"),
    Routine(one_roller_right, start_position_e::BOTH, "Set One Roller"),
    Routine(both_rollers_right, start_position_e::LEFT, "Set Both Rollers"),
    Routine(both_rollers_left, start_position_e::RIGHT, "Set Both Rollers"),
    Routine(awp_left, start_position_e::RIGHT, "Set Both Rollers"),
    Routine(awp_right, start_position_e::RIGHT, "Set Both Rollers")};
