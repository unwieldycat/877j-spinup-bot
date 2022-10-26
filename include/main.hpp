#pragma once

// Libraries
#include "api.h"
#include "okapi/api.hpp"
#include <functional>
#include <iostream>

using namespace okapi::literals;

// Team enum
enum team_e { TEAM_NEUTRAL = 0, TEAM_RED = 1, TEAM_BLUE = 2 };

// Globals
extern int team;

// Function prototypes
extern "C" {
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
}
