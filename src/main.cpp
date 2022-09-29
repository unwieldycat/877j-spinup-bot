#include "main.hpp"
#include "devices.hpp"
#include "gui.hpp"
#include "manual.hpp"

// ============================= Initalization ============================= //

void initialize() {
	gui::init();
	gui::team_selection();  // temp
	gui::auton_selection(); // temp
}

void competition_initialize() {}

// ============================== Main Methods ============================== //

void disabled() {}

void autonomous() {}

void opcontrol() { pros::Task drive_task(manual::drive_control); }
