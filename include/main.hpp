#pragma once

// Libraries
#include "api.h"
#include "okapi/api.hpp"
#include <iostream>

using namespace okapi::literals;

// Function prototypes
extern "C" {
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
}
