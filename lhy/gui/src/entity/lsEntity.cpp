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

/**
 * @brief Entity scale relative to Origin
 * 
 * @param entity 
 * @param scalex 
 * @param scaley 
 * @return lsEntity 
 */
lsEntity ls_entity_scale(const lsEntity *entity, lsReal scalex, lsReal scaley)
{
    lsEntity ent;

    switch (entity->type)
    {
    case kLine:
        ent.data.line = ls_line_scale(&entity->data.line, scalex, scaley);
        ent = ls_entity_convert_line(&ent.data.line);
        break;

    case kCircle:
        ent.data.circle = ls_circle_scale(&entity->data.circle, scalex);
        ent = ls_entity_convert_circle(&ent.data.circle);
        break;

    default:
        ent.type = kUnknown;
        break;
    }

    return ent;
}

/**
 * @brief 实体以 \p center 为不动点进行缩放。即放缩前后 \p center 是不动的。
 * 
 * @param entity 
 * @param center 
 * @param scalex 
 * @param scaley 
 * @return lsEntity 
 */
lsEntity ls_entity_center_scale(const lsEntity *entity, const lsPoint *center, lsReal scalex, lsReal scaley)
{
    lsPoint transToOrigin = *center;
    ls_point_negative(&transToOrigin);

    lsEntity ent = *entity;
    ent = ls_entity_translate(&ent, &transToOrigin);// move to origin
    ent = ls_entity_scale(&ent, scalex, scaley);// scale relative to origin
    ent = ls_entity_translate(&ent, center);// back to center
    return ent;
}

lsEntity ls_entity_translate(const lsEntity *entity, const lsPoint *vector)
{
    lsEntity ent;

    switch (entity->type)
    {
    case kLine:
        ent.data.line = ls_line_translate(&entity->data.line, vector);
        ent = ls_entity_convert_line(&ent.data.line);
        break;
        
    case kCircle:
        ent.data.circle = ls_circle_translate(&entity->data.circle, vector);
        ent = ls_entity_convert_circle(&ent.data.circle);
        break;

    default:
        ent.type = kUnknown;
        break;
    }

    return ent;
}
