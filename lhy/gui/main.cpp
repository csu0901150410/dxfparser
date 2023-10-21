#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <iostream>

#include "lsCanvas.h"

int main()
{
	lsCanvas canvas;

	std::cout << "Press any key to exit..." << std::endl;
	
	ls_canvas_init(&canvas, 800, 600);

	// 加实体
	ls_canvas_add_entity(&canvas, ls_entity_make_line(100, 500, 300, 500));
	ls_canvas_add_entity(&canvas, ls_entity_make_circle(300, 300, 150));

	ls_canvas_polling(&canvas);
	ls_canvas_destroy(&canvas);

	return 0;
}