#ifndef LS_ENTITY_H
#define LS_ENTITY_H

#define _CRT_SECURE_NO_WARNINGS

#include "lsPoint.h"
#include "lsLine.h"
#include "lsCircle.h"
#include "lsBoundbox.h"
#include "lsArc.h"

typedef enum
{
    kUnknown = 0,
    kPoint,
    kLine,
    kArc,
    kCircle,
    kXLine
} EntityType;

typedef union
{
    lsPoint point;
    lsLine line;
    lsCircle circle;
    lsArc arc;
} EntityData;

typedef struct
{
    EntityType type;
    EntityData data;
} lsEntity;

/**
 * @brief Convert lsPoint to lsEntity
 * 
 * @param point pointer to point
 * @return lsEntity 
 */
lsEntity ls_entity_convert_point(const lsPoint *point);

/**
 * @brief Convert lsLine to lsEntity
 * 
 * @param line pointer to line
 * @return lsEntity 
 */
lsEntity ls_entity_convert_line(const lsLine *line);

/**
 * @brief Convert lsCircle to lsEntity
 * 
 * @param circle pointer to circle
 * @return lsEntity 
 */
lsEntity ls_entity_convert_circle(const lsCircle *circle);

/**
 * @brief Convert lsArc to lsEntity
 * 
 * @param arc pointer to arc
 * @return lsEntity 
 */
lsEntity ls_entity_convert_arc(const lsArc *arc);

/**
 * @brief Get the boundbox of the entity
 * 
 * @param entity 
 * @return lsBoundbox 
 */
lsBoundbox ls_entity_get_boundbox(const lsEntity *entity);

lsBoundbox ls_entity_get_boundbox(const std::vector<lsEntity> &entitys);

/**
 * @brief Entity scale relative to Origin
 * 
 * @param entity 
 * @param scale 
 * @return lsEntity 
 */
lsEntity ls_entity_scale(const lsEntity *entity, lsReal scale);

lsEntity ls_entity_translate(const lsEntity *entity, const lsVector *vector);

lsEntity ls_entity_scale_ref(const lsEntity *entity, const lsPoint *center, lsReal scale);

lsEntity ls_entity_transform(const lsEntity *entity, const lsCoordSystem *cs);

#endif // LS_ENTITY_H
