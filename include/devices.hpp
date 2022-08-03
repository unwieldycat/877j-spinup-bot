#pragma once

#include "main.hpp"

// =========================== Device Definitions =========================== //

// Inputs
extern okapi::Controller controller;

// Motors
extern okapi::Motor drive_fl;
extern okapi::Motor drive_fr;
extern okapi::Motor drive_rl;
extern okapi::Motor drive_rr;

// Chassis
extern std::shared_ptr<okapi::OdomChassisController> chassis;