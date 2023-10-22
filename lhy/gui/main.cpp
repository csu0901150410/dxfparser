#include <graphics.h>
#include <conio.h>
#include <iostream>

#include "lsCanvas.h"
#include "lsDxf.h"

// error C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead. 
// To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

int main()
{
	lsDxf dxflib;
	ls_dxf_init(&dxflib, "../res/demo_2023102200.dxf");
	ls_dxf_parse(&dxflib);
	ls_dxf_result_print(&dxflib);

	lsCanvas canvas;

	std::cout << "Press any key to exit..." << std::endl;
	
	ls_canvas_init(&canvas, 800, 600);

	ls_canvas_add_entity(&canvas, ls_entity_make_line(100, 500, 300, 500));
	ls_canvas_add_entity(&canvas, ls_entity_make_circle(300, 300, 150));

	ls_canvas_polling(&canvas);
	ls_canvas_destroy(&canvas);

	return 0;
}