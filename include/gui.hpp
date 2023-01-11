#pragma once

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
void auton_selection();

/**
 * Open team selection UI
 *
 * Returns int
 */
void team_selection();

/**
 * Show game UI
 */
void game();

} // namespace gui
