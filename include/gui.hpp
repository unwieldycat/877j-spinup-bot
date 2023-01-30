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
 * Open autonomous selection window
 *
 * Returns auton selected by user
 */
auton::action_t auton_selection();

/**
 * Show game UI
 */
void game();

} // namespace gui
