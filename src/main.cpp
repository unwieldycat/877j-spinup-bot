#include "main.hpp"
#include "auton.hpp"
#include "devices.hpp"
#include "gui.hpp"

// =============================== Variables ================================ //

auton::action_t auton_routine = auton::do_nothing;

// ============================= Initalization ============================= //

void initialize() {
	std::cout << "[INFO] Initializing GUI" << std::endl;
	gui::init();

	// Reset inertial or else it'll return "inf"
	std::cout << "[INFO] Calibrating inertial" << std::endl;
	inertial.reset();
	while (inertial.is_calibrating())
		pros::delay(500);
	std::cout << "[INFO] Inertial calibrated" << std::endl;
}

void competition_initialize() { auton_routine = gui::auton_selection(); }

// ============================== Main Methods ============================== //

void disabled() {}

void autonomous() {
	// Run auton routine
	auton_routine();
}

void opcontrol() {
	//  Drive control tasks
	pros::Task drive_task(drive_control);
	pros::Task launch_task(launch_control);
	pros::Task roller_task(roller_control);
	pros::Task expansion_task(expand_control);
	pros::Task indexer_task(manual_push);
}
