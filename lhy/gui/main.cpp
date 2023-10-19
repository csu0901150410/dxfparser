#include <easyx.h>
#include <conio.h>

// Reference : https://docs.easyx.cn/zh-cn/intro

int main()
{

    initgraph(800, 600);

    setbkcolor(BLACK);
    cleardevice();

    setlinecolor(WHITE);

    circle(800 / 2, 600 / 2, 100);

    // BeginBatchDraw();
    // FlushBatchDraw();
    // EndBatchDraw();

    while (1)
    {
        if (_kbhit())
            break;
    }

    closegraph();

    return 0;
}

