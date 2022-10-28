#pragma once

#include "devices.hpp"
#include "main.hpp"

// ================== Manual Control Function Definitions ================== //

namespace manual {

/**
 * Activates manual control for drivetrain
 */
void drive_control();

/**
 *  Manual control for launcher
 */
void launch_control();

} // namespace manual