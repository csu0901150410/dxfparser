#include "lsEntity.h"

/**
 * @brief Convert lsPoint to lsEntity
 * 
 * @param point pointer to point
 * @return lsEntity 
 */
lsEntity ls_entity_convert_point(lsPoint *point)
{
    lsEntity entity;
    entity.type = kPoint;
    entity.data.point = *point;
    return entity;
}

/**
 * @brief Convert lsLine to lsEntity
 * 
 * @param line pointer to line
 * @return lsEntity 
 */
lsEntity ls_entity_convert_line(lsLine *line)
{
    lsEntity entity;
    entity.type = kLine;
    entity.data.line = *line;
    return entity;
}

/**
 * @brief Convert lsCircle to lsEntity
 * 
 * @param circle pointer to circle
 * @return lsEntity 
 */
lsEntity ls_entity_convert_circle(lsCircle *circle)
{
    lsEntity entity;
    entity.type = kCircle;
    entity.data.circle = *circle;
    return entity;
}

/**
 * @brief Get the boundbox of the entity
 * 
 * @param entity 
 * @return lsBoundbox 
 */
lsBoundbox ls_entity_get_boundbox(lsEntity *entity)
{
    lsBoundbox box;

    switch (entity->type)
    {
    case kLine:
        box = ls_line_get_boundbox(&entity->data.line);
        break;

    case kCircle:
        box = ls_circle_get_boundbox(&entity->data.circle);
        break;

    default:
        break;
    }

    return box;
}

lsEntity ls_entity_scale(const lsEntity *entity, lsReal scalex, lsReal scaley)
{
    lsEntity ent;
    lsLine line;
    lsCircle circle;

    switch (entity->type)
    {
    case kLine:
        line = ls_line_scale(&entity->data.line, scalex, scaley);
        ent = ls_entity_convert_line(&line);
        break;

    case kCircle:
        circle = ls_circle_scale(&entity->data.circle, scalex);
        ent = ls_entity_convert_circle(&circle);
        break;

    default:
        ent.type = kUnknown;
        break;
    }

    return ent;
}
