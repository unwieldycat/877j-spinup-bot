#pragma once

#include "main.hpp"

// =========================== Device Definitions =========================== //

// Inputs
extern okapi::Controller controller;

// Sensors
extern pros::Distance distance;
extern pros::Optical optical;

// Motors
extern okapi::Motor drive_fl;
extern okapi::Motor drive_fr;
extern okapi::Motor drive_rl;
extern okapi::Motor drive_rr;

extern pros::Motor roller;
extern pros::Motor launcher;
extern pros::Motor intake;

// Chassis
extern std::shared_ptr<okapi::OdomChassisController> chassis;

// Functions
extern void auto_roller(void);
extern void roller_control(void);
extern void drive_control(void);
extern void launch_control(void);