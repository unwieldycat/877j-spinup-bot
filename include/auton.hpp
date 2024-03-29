#pragma once

#include "devices.hpp"
#include "main.hpp"

// ===================== Autonomous System Definitions ===================== //

namespace auton {

/**
 * Type for autonomous functions
 */
typedef std::function<void()> action_t;

/**
 * Side of the field the robot will start on
 */
enum class start_position_e { LEFT, RIGHT, BOTH };

/**
 * Routine data structure
 */
struct Routine {
	inline Routine(action_t act, start_position_e pos, std::string desc) {
		description = desc;
		start_pos = pos;
		action = act;
	}

	std::string description;
	start_position_e start_pos;
	action_t action;
};

/**
 * Do nothing function (default routine)
 */
action_t do_nothing();

/**
 * Vector of Routine struct instances
 */
extern std::vector<Routine> routines;

/**
 * The skills routine
 */
void skills();

} // namespace auton
