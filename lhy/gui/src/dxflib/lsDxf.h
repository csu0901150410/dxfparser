#ifndef LS_DXF_H
#define LS_DXF_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <vector>

#include "lsPoint.h"
#include "lsLine.h"

typedef struct
{
    FILE *fp;// DXF文件指针

    char stringLine[1024];// DXF文件行字符串

    // extract data
    std::vector<lsLine> lines;// entity::line data
} lsDxf;

bool ls_dxf_init(lsDxf *dxf, const char *filepath);

bool ls_dxf_get_line(lsDxf *dxf);

bool ls_dxf_read_entity_line(lsDxf *dxf);

void ls_dxf_parse(lsDxf *dxf);

void ls_dxf_result_print(lsDxf *dxf);

#endif // LS_DXF_H
