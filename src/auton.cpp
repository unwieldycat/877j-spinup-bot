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
void solo_awp_left() {}

void solo_awp_right() {}

/**
 * Only push discs into low goal
 */
void preload() { /*chassis->moveDistance(-2_ft);*/
}

// TODO: Simple roller routines
void one_roller_left() {}

void one_roller_right() {}

/**
 * Do both rollers and ignore discs (starting from left)
 */
void both_rollers_left() {}

/**
 * Do both rollers and ignore discs (starting from right)
 */
void both_rollers_right() {}

// ============================ Routine Metadata ============================ //

std::vector<Routine> auton::routines{
    Routine(do_nothing, start_position_e::BOTH, "Do nothing"),
    Routine(solo_awp_left, start_position_e::LEFT, "Solo Autonomous Win Point (Left)"),
    Routine(solo_awp_right, start_position_e::LEFT, "Solo Autonomous Win Point (Right)"),
    Routine(preload, start_position_e::BOTH, "Push discs into low goal"),
    Routine(one_roller_right, start_position_e::RIGHT, "Set One Roller (Right)"),
    Routine(one_roller_left, start_position_e::LEFT, "Set One Roller (Left)"),
    Routine(both_rollers_right, start_position_e::LEFT, "Set Both Rollers (Right)"),
    Routine(both_rollers_left, start_position_e::RIGHT, "Set Both Rollers (Left)")};
