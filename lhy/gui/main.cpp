#include <easyx.h>
#include <conio.h>

#include "HiEasyX.h"

int main()
{
	initgraph();			// 初始化窗口

	BEGIN_TASK();			// （不同于 EasyX）启动任务，标识开始绘制

	circle(320, 240, 100);	// 画圆

	END_TASK();				// （不同于 EasyX）完成绘制，结束任务

	REDRAW_WINDOW();		// （不同于 EasyX）刷新屏幕，使刚才绘制的内容显示出来

	getmessage(EM_KEY);		// 任意键退出

	closegraph();			// 关闭窗口
	return 0;
}

