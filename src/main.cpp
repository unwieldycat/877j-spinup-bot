#include "main.hpp"
#include "devices.hpp"
#include "gui.hpp"
#include "manual.hpp"

// =============================== Variables ================================ //

int team;
auton::action_t auton_routine;

// ============================= Initalization ============================= //

void initialize() { gui::init(); }

void competition_initialize() {
	team = gui::team_selection();
	auton_routine = gui::auton_selection();
}

// ============================== Main Methods ============================== //

void disabled() {}

void autonomous() {}

void opcontrol() { pros::Task drive_task(manual::drive_control); }
