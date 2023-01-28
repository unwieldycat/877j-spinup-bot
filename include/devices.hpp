#pragma once

#define CHASSIS_WIDTH
#define WHEEL_DIAMETER 2.75

#include "main.hpp"

// =========================== Device Definitions =========================== //

// Inputs
extern pros::Controller controller;

// Sensors
extern pros::Imu inertial;

// Motors
extern pros::Motor drive_fl;
extern pros::Motor drive_fr;
extern pros::Motor drive_rl;
extern pros::Motor drive_rr;

extern pros::Motor expansion;
extern pros::Motor launcher;
extern pros::Motor roller;
extern pros::Motor pusher;

extern pros::Rotation rotation_long;
extern pros::Rotation rotation_lat;

// Chassis functions
/**
 * Drive a given distance
 *
 * \param dist Distance in inches
 * \param strafe Whether to move sideways (forward is right)
 */
extern void drive_distance(int dist, bool strafe = false);

/**
 * Turn a certain angle
 *
 * \param desired_hdg angle to turn
 */
extern void turn(int desired_hdg);

extern void drive_power(int power, int msecs, bool strafe = false);

// Other functions
extern void auto_roller(void);
extern void roller_control(void);
extern void drive_control(void);
extern void launch_control(void);
extern void expand_control(void);
extern void manual_push(void);