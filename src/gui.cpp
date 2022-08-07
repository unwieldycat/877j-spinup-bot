#include "gui.hpp"
#include "devices.hpp"

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
	sprintf(buf, "/%s", fn);
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

static lv_fs_res_t fs_read(void *file_p, void *buf, uint32_t btr,
                           uint32_t *br) {
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

auton::Routine gui::selection() {
	lv_obj_t *select_scr = lv_page_create(NULL, NULL);
	lv_scr_load(select_scr);
}

// ================================ Game UI ================================ //

void gui::game() {
	lv_obj_t *game_scr = lv_page_create(NULL, NULL);
	lv_scr_load(game_scr);
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
