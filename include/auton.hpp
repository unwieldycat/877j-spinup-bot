#pragma once

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
 * Vector of Routine struct instances
 */
extern std::vector<Routine> routines;

/**
 * The skills routine
 */
action_t skills();

} // namespace auton
