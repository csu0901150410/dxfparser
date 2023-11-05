#ifndef LS_ARC_H
#define LS_ARC_H

#include "lsPoint.h"
#include "lsBoundbox.h"

//typedef struct
//{
//    lsPoint lup;
//    lsPoint rlow;
//    lsReal stangle;
//    lsReal endangle;
//}lsArc;
//
//lsBoundbox ls_arc_get_boundbox(lsArc* arc);
//
//lsArc ls_arc_scale(const lsArc* arc, lsReal scalex, lsReal scaley);
//
//lsArc ls_arc_translate(const lsArc* arc, const lsPoint* vector);


typedef struct
{
    lsPoint s;
    lsPoint e;
    lsPoint c;
    bool bccw;
    bool valid;
} lsArc;

/**
 * @brief �����㹹��Բ��
 * Ref : https://stackoverflow.com/questions/52990094/calculate-circle-given-3-points-code-explanation
 *
 * @param s
 * @param a
 * @param e
 * @return lsArc
 */
lsArc ls_arc_construct_from_ppp(lsPoint s, lsPoint a, lsPoint e);

/**
 * @brief ��ȡԲ���뾶
 *
 * @param arc
 * @return lsReal
 */
lsReal ls_arc_get_radius(lsArc* arc);

/**
 * @brief ��ȡԲ������
 *
 * @param arc
 * @return lsReal
 */
lsReal ls_arc_get_radian(lsArc* arc);

/**
 * @brief ��ȡԲ����ʼ����
 *
 * @param arc
 * @return lsReal
 */
lsReal ls_arc_get_start_angle(lsArc* arc);

/**
 * @brief ��ȡԲ����ֹ����
 *
 * @param arc
 * @return lsReal
 */
lsReal ls_arc_get_end_angle(lsArc* arc);

/**
 * @brief ��ȡԲ������Բ��Χ��
 *
 * @param arc
 * @return lsBoundbox
 */
lsBoundbox ls_arc_get_circle_boundbox(lsArc* arc);

/**
* @brief Բ��������
* 
* @param arc scale
* @return lsReal
*/
lsArc ls_arc_scale(const lsArc* arc, lsReal scalex,lsReal scaley);

lsArc ls_arc_translate(const lsArc* arc, const lsPoint* vector);

// lhy test
#include "easyx.h"
void ls_arc_draw(lsArc* circlearc);

#endif // LS_ARC_H
