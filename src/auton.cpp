#include "auton.hpp"

// =================== Routine Constructor Implementation =================== //

auton::Routine::Routine(std::string _name, auton::start_position_e _pos,
                        auton::action_t _action) {
	name = _name;
	start_pos = _pos;
	action = _action;
}

// ============================= Skills Routine ============================= //

void auton::skills() {}

// ============================= Match Routines ============================= //

// Reference routine for future
auton::Routine example("Example", auton::start_position_e::LEFT, []() {

});

// Register all routines here
std::vector<auton::Routine> auton::routines{example};
