#pragma once

#include "main.hpp"

// ============================ GUI Definitions ============================ //

namespace gui {

/**
 * Initialize GUI and show startup screen
 */
void init();

/**
 * Show autonomous selection prompt
 */
int selection();

/**
 * Show autonomous status screen
 */
void auton();

/**
 * Show operator control status screen
 */
void opcontrol();

} // namespace gui
