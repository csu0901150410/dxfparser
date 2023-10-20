#include <graphics.h>		// 引用图形库头文件
#include <conio.h>

int main()
{
	initgraph(640, 480);	// 创建绘图窗口，大小为 640x480 像素
	circle(200, 200, 100);	// 画圆，圆心(200, 200)，半径 100

	while (1)
	{
		if (_kbhit())
			break;
	}

	closegraph();			// 关闭绘图窗口
	return 0;
}