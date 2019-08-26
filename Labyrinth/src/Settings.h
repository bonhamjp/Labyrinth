#pragma once

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

// Must be in range (0-1]
#define RESOLUTION 0.5f

#define COLOR_BUFFER_WIDTH (WINDOW_WIDTH * RESOLUTION)
#define COLOR_BUFFER_HEIGHT (WINDOW_HEIGHT * RESOLUTION)

#define WINDOW_TITLE "Labyrinth"

#define FPS 30

#define WALL_SIZE 32

#define MAP_COLUMNS 6 // 62
#define MAP_ROWS 6 // 62

#define FIELD_OF_VIEW 60

#define SKY_COLOR 0x42bfe8FF
#define FLOOR_COLOR 0x696682FF

#define SAVE_FILE_NAME "previous_run_time.txt"
