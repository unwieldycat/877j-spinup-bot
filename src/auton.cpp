#include "auton.hpp"

using namespace auton;

// ============================= Skills Routine ============================= //

void auton::skills() {
	/*intake.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	pusher.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	chassis->driveToPoint({1_ft, 0.5_ft});
	intake.move_absolute(210, 100);
	chassis->driveToPoint({1_ft, -1_ft});
	chassis->turnAngle(-90_deg);
	launcher.move(127);
	chassis->driveToPoint({3_ft, -2.5_ft});
	intake.move_relative(210, 100);
	chassis->driveToPoint({3_ft, -2.25_ft});
	chassis->turnToAngle(0_deg);
	pusher.move_relative(360, 100);
	pros::delay(2000);
	pusher.move_relative(360, 100);
	chassis->driveToPoint({-4_ft, -5_ft});
	launcher.move(0);
	chassis->driveToPoint({-7_ft, -10_ft});
	chassis->turnToAngle(-180_deg);
	chassis->driveToPoint({-7_ft, -11.25_ft});
	intake.move_relative(210, 100);
	chassis->driveToPoint({-8_ft, -9_ft});
	chassis->turnToAngle(90_deg);
	chassis->driveToPoint({-9.25_ft, -9_ft});
	intake.move_relative(210, 100);
	chassis->driveToPoint({-8.5_ft, -8_ft});*/
}

// ============================= Match Routines ============================= //

/**
 * For when our alliance partner has an infinitely better routine
 */
void do_nothing() {}

/**
 * Win point routine
 * TODO: Make work
 */
void solo_awp_left() {
	/*chassis->setState({0_ft, 0_ft, 0_deg});
	intake.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	pusher.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	chassis->driveToPoint({100_ft, 0_ft});
	pros::delay(2000);*/
}

void solo_awp_right() {
	/*intake.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	pusher.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	chassis->driveToPoint({-2_ft, 0.5_ft});
	intake.move_relative(180, 100);
	chassis->driveToPoint({4_ft, -4_ft});
	launcher.move(127);
	chassis->turnToAngle(135_deg);
	pusher.move_relative(360, 100);
	pros::delay(2000);
	pusher.move_relative(360, 100);
	chassis->driveToPoint({5_ft, -8.5_ft});
	launcher.move(0);
	chassis->turnToAngle(-90_deg);
	chassis->driveToPoint({6.5_ft, 8.5_ft});
	intake.move_relative(180, 100);*/
}

/**
 * Only push discs into low goal
 */
void preload() { /*chassis->moveDistance(-2_ft);*/
}

// TODO: Simple roller routines
void one_roller_left() {
	/*intake.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	chassis->driveToPoint({0_ft, 0.5_ft});
	intake.move_absolute(180, 100);*/
}
void one_roller_right() {
	/*intake.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	chassis->driveToPoint({-2_ft, 0.5_ft});
	intake.move_absolute(180, 100);*/
}

/**
 * Do both rollers and ignore discs (starting from left)
 */
void both_rollers_left() {
	/*intake.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	chassis->driveToPoint({1_ft, 0.5_ft});
	intake.move_relative(180, 100);
	chassis->driveToPoint({-4_ft, -4_ft});
	chassis->turnToAngle(90_deg);
	chassis->driveToPoint({-7_ft, -9_ft});
	chassis->driveToPoint({-9.5_ft, -9_ft});
	intake.move_relative(180, 100);
	chassis->driveToPoint({-9_ft, -9_ft});*/
}

/**
 * Do both rollers and ignore discs (starting from right)
 */
void both_rollers_right() {
	/*intake.set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
	chassis->driveToPoint({-2_ft, 0.5_ft});
	intake.move_relative(180, 100);
	chassis->driveToPoint({4_ft, -4_ft});
	chassis->driveToPoint({5_ft, -8.5_ft});
	chassis->turnToAngle(-90_deg);
	chassis->driveToPoint({6.5_ft, 8.5_ft});
	intake.move_relative(180, 100);*/
}

// ============================ Routine Metadata ============================ //

std::vector<Routine> auton::routines{
    Routine(do_nothing, start_position_e::BOTH, "Do nothing"),
    Routine(solo_awp_left, start_position_e::LEFT, "Solo Autonomous Win Point (Left)"),
    Routine(solo_awp_right, start_position_e::LEFT, "Solo Autonomous Win Point (Right)"),
    Routine(preload, start_position_e::BOTH, "Push discs into low goal"),
    Routine(one_roller_right, start_position_e::RIGHT, "Set One Roller (Right)"),
    Routine(one_roller_left, start_position_e::LEFT, "Set One Roller (Left)"),
    Routine(both_rollers_right, start_position_e::LEFT, "Set Both Rollers (Right)"),
    Routine(both_rollers_left, start_position_e::RIGHT, "Set Both Rollers (Left)")};
