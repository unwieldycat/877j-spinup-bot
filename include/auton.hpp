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
enum class start_position_e { LEFT, RIGHT };

/**
 * Routine data structure
 */
struct Routine {
	Routine(std::string _name, start_position_e _pos, action_t _action);
	std::string name;
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
void skills();

} // namespace auton
