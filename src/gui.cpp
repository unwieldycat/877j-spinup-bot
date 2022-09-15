#include "gui.hpp"
#include "pros/misc.hpp"

// ====================== Filesystem Driver Functions ====================== //

// Credit to jpearman on VEXFourm for the filesystem driver functions
// https://www.vexforum.com/t/lvgl-image-not-displaying/63612/14

static lv_fs_res_t fs_open(void *file_p, const char *fn, lv_fs_mode_t mode) {
	errno = 0;
	const char *flags = "";
	if (mode == LV_FS_MODE_WR)
		flags = "wb";
	else if (mode == LV_FS_MODE_RD)
		flags = "rb";
	else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
		flags = "a+";

	char buf[256];
	sprintf(buf, "/usd/%s", fn);
	FILE *f = fopen(buf, flags);

	if (f == NULL)
		return LV_FS_RES_UNKNOWN;
	else {
		fseek(f, 0, SEEK_SET);
		FILE **fp = (FILE **)file_p;
		*fp = f;
	}

	return LV_FS_RES_OK;
}

static lv_fs_res_t fs_close(void *file_p) {
	FILE **fp = (FILE **)file_p;
	fclose(*fp);
	return LV_FS_RES_OK;
}

static lv_fs_res_t fs_read(void *file_p, void *buf, uint32_t btr, uint32_t *br) {
	FILE **fp = (FILE **)file_p;
	*br = fread(buf, 1, btr, *fp);
	return LV_FS_RES_OK;
}

static lv_fs_res_t fs_seek(void *file_p, uint32_t pos) {
	FILE **fp = (FILE **)file_p;
	fseek(*fp, pos, SEEK_SET);
	return LV_FS_RES_OK;
}

static lv_fs_res_t fs_tell(void *file_p, uint32_t *pos_p) {
	FILE **fp = (FILE **)file_p;
	*pos_p = ftell(*fp);
	return LV_FS_RES_OK;
}

// =========================== Auton Selector UI =========================== //

int selected_r_id;

// Select action for routine buttons
lv_res_t r_select_act(lv_obj_t *obj) {
	int id = lv_obj_get_free_num(obj);
	selected_r_id = id;
	std::cout << id << std::endl;
	return LV_RES_OK;
}

bool user_is_done = false;

// Action for done button
lv_res_t done_act(lv_obj_t *obj) {
	user_is_done = true;
	return LV_RES_OK;
}

auton::action_t gui::selection() {
	// Save pointer to main screen and create new screen for selection
	lv_obj_t *main_scr = lv_scr_act();
	lv_obj_t *select_scr = lv_obj_create(NULL, NULL);
	lv_scr_load(select_scr);

	// Title
	lv_obj_t *title = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(title, "Select autonomous routine");
	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 8);

	// Routines list
	lv_obj_t *r_list = lv_list_create(lv_scr_act(), NULL);
	lv_obj_align(r_list, NULL, LV_ALIGN_IN_TOP_LEFT, 8, 32);
	lv_obj_set_size(r_list, 232, 160);

	// Add routines to list
	for (auton::Routine r : auton::routines) {
		// Store index in vector
		static int r_index = 0;

		// Set lvgl button id
		lv_obj_t *new_btn = lv_list_add(r_list, NULL, r.description.c_str(), r_select_act);
		lv_obj_set_free_num(new_btn, r_index);
		lv_btn_set_action(new_btn, LV_BTN_ACTION_CLICK, &r_select_act);

		r_index++;
	}

	// Button for skills
	lv_obj_t *skills_btn = lv_list_add(r_list, NULL, "Skills", r_select_act);

	// Register skills button
	lv_obj_set_free_num(skills_btn, -1);

	// Done button
	lv_obj_t *done = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_align(done, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 8, 8);
	lv_obj_set_pos(done, 8, 200);
	lv_obj_set_size(done, 232, 32);
	lv_btn_set_action(done, LV_BTN_ACTION_CLICK, &done_act);
	lv_obj_t *done_label = lv_label_create(done, NULL);
	lv_label_set_text(done_label, "Done");

	// Wait for user to be done or for match to start
	const bool match_has_started =
	    (pros::competition::is_connected() && !pros::competition::is_disabled());

	while (!user_is_done || match_has_started)
		pros::delay(100);

	// Reset screen
	lv_scr_load(main_scr);

	// Return selected routine
	if (selected_r_id == -1) return auton::skills;
	auton::Routine routine = auton::routines.at(selected_r_id);
	return routine.action;
}

// ================================ Game UI ================================ //

void gui::game() {
	lv_obj_t *game_scr = lv_page_create(NULL, NULL);
	lv_scr_load(game_scr);

	// TODO: Make game UI
}

// ================================ Methods ================================ //

void gui::init() {
	// Create and configure filesystem driver
	lv_fs_drv_t fs_driver;
	memset(&fs_driver, 0, sizeof(lv_fs_drv_t));
	fs_driver.file_size = sizeof(FILE *);
	fs_driver.letter = 'S';
	fs_driver.open = fs_open;
	fs_driver.close = fs_close;
	fs_driver.read = fs_read;
	fs_driver.seek = fs_seek;
	fs_driver.tell = fs_tell;
	lv_fs_add_drv(&fs_driver);

	// TODO: Splash screen
}
