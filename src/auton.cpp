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
void one_roller() {}

/**
 * Do both rollers and ignore discs
 */
void both_rollers() {}

// ============================ Routine Metadata ============================ //

std::vector<Routine> routines{
    Routine(solo_awp, start_position_e::LEFT, "Solo Autonomous Win Point"),
    Routine(one_roller, start_position_e::BOTH, "One Roller"),
    Routine(both_rollers, start_position_e::RIGHT, "Set Both Rollers")};
