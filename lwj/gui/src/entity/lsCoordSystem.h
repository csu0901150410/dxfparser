#ifndef LS_COORD_SYSTEM_H
#define LS_COORD_SYSTEM_H

#include "lsVector.h"

typedef struct
{
    lsVector origin;// ����ϵԭ���������������ϵ��ƽ������
    lsReal scale;// ����ϵ�������������ϵ������ϵ��
} lsCoordSystem;

#endif // LS_COORD_SYSTEM_H