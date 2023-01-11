#pragma once

#define PI 3.14159265358979323846

// Libraries
#include "api.h"
#include <functional>
#include <iostream>
#include <math.h>

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
