#pragma once

#include "auton.hpp"
#include "main.hpp"

// ============================ GUI Definitions ============================ //

namespace gui {

/**
 * Initialize GUI and load screen elements
 */
void init();

/**
 * Show autonomous selection UI
 *
 * Returns auton selected by user
 */
auton::action_t selection();

/**
 * Show game UI
 */
void game();

} // namespace gui
