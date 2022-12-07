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
 * Win point routine
 */
void solo_awp() {
	launcher.move(127);
	auto_roller();
	chassis->driveToPoint({-5.5_ft, -5.5_ft});
	chassis->turnToAngle(135_deg);
}

/**
 * Only push discs into low goal
 */
void preload() { chassis->driveToPoint({2_ft, 0_ft}); }

// TODO: Simple roller routines
void one_roller_left() { auto_roller(); }
void one_roller_right() {
	chassis->driveToPoint({-1_ft, 0_ft});
	auto_roller();
}

/**
 * Do both rollers and ignore discs (starting from left)
 */
void both_rollers_left() {
	auto_roller();
	chassis->driveToPoint({-5_ft, -5_ft});
	chassis->turnToAngle(-90_deg);
	chassis->driveToPoint({-11_ft, -11_ft});
	auto_roller();
}

/**
 * Do both rollers and ignore discs (starting from right)
 */
void both_rollers_right() {
	chassis->driveToPoint({-1.5_ft, 0_ft});
	auto_roller();
	chassis->driveToPoint({5_ft, 5_ft});
	chassis->driveToPoint({11_ft, 11_ft});
	chassis->turnToAngle(90_deg);
	auto_roller();
}

// ============================ Routine Metadata ============================ //

std::vector<Routine> auton::routines{
    Routine(do_nothing, start_position_e::BOTH, "Do nothing"),
    Routine(solo_awp, start_position_e::LEFT, "Solo Autonomous Win Point"),
    Routine(preload, start_position_e::BOTH, "Push discs into low goal"),
    Routine(one_roller_right, start_position_e::RIGHT, "Set One Roller"),
    Routine(one_roller_left, start_position_e::LEFT, "Set One Roller"),
    Routine(both_rollers_right, start_position_e::LEFT, "Set Both Rollers"),
    Routine(both_rollers_left, start_position_e::RIGHT, "Set Both Rollers")};
