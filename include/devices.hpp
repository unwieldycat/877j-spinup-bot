#pragma once

// TODO: Tune PID

#define KP 0.5
#define KI 0.2
#define KD 0.1

#define CHASSIS_WIDTH
#define WHEEL_RADIUS 2.5

#include "main.hpp"

// =========================== Device Definitions =========================== //

// Inputs
extern pros::Controller controller;

// Sensors
extern pros::Distance distance;
extern pros::Optical optical;

// Motors
extern pros::Motor drive_fl;
extern pros::Motor drive_fr;
extern pros::Motor drive_rl;
extern pros::Motor drive_rr;

extern pros::Motor roller;
extern pros::Motor launcher;
extern pros::Motor intake;
extern pros::Motor pusher;

// Chassis functions
extern void drive_distance(int dist);
extern void turn(int desired_hdg);

// Other functions
extern void auto_roller(void);
extern void roller_control(void);
extern void drive_control(void);
extern void launch_control(void);
extern void expand_control(void);
extern void manual_push(void);