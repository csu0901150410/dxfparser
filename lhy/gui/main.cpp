#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>

int main()
{
	initgraph(640, 480);	// ������ͼ���ڣ���СΪ 640x480 ����
	circle(200, 200, 100);	// ��Բ��Բ��(200, 200)���뾶 100

	while (1)
	{
		if (_kbhit())
			break;
	}

	closegraph();			// �رջ�ͼ����
	return 0;
}