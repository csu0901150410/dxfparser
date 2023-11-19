#include <graphics.h>
#include <conio.h>
#include <iostream>

#include "lsCanvas.h"
#include "lsDxf.h"

#include "lsRandom.h"

// error C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead. 
// To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

int main()
{
	InitRandom();

	// lsDxf dxflib;
	// ls_dxf_init(&dxflib, "../res/demo_2023102200.dxf");
	// ls_dxf_parse(&dxflib);
	// ls_dxf_result_print(&dxflib);

	lsCanvas canvas;
	ls_canvas_init(&canvas, 800, 600);

	ls_canvas_load_entity_test(&canvas);
	// ls_canvas_load_entity(&canvas, &dxflib.entitys);

	ls_canvas_polling(&canvas);
	ls_canvas_destroy(&canvas);

	return 0;
}