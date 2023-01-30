#pragma once

#define PI 3.14159265358979323846

// Libraries
#include "api.h"
#include <functional>
#include <iostream>
#include <math.h>

// Function prototypes
extern "C" {
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
}
