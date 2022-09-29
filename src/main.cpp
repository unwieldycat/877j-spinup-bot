#include "main.hpp"
#include "devices.hpp"
#include "gui.hpp"
#include "manual.hpp"

// ============================= Initalization ============================= //

void initialize() { gui::init(); }

void competition_initialize() {
	gui::team_selection();
	gui::auton_selection();
}

// ============================== Main Methods ============================== //

void disabled() {}

void autonomous() {}

void opcontrol() { pros::Task drive_task(manual::drive_control); }
