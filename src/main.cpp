#include "main.hpp"
#include "devices.hpp"
#include "gui.hpp"

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

void autonomous() {
	// Reset motor directionality in event of change
	drive_fl.setReversed(false);
	drive_fr.setReversed(true);
	drive_rl.setReversed(false);
	drive_rr.setReversed(true);

	// Run auton routine
	auton_routine();
}

void opcontrol() {
	// Drive control tasks
	pros::Task drive_task(drive_control);
	pros::Task launch_task(launch_control);
	pros::Task roller_task(roller_control);
	pros::Task expansion_task(expand_control);
	pros::Task indexer_task(manual_push);
}
