#include "vector"

#include "lsEntity.h"

/**
 * @brief Convert lsPoint to lsEntity
 * 
 * @param point pointer to point
 * @return lsEntity 
 */
lsEntity ls_entity_convert_point(const lsPoint *point)
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
lsEntity ls_entity_convert_line(const lsLine *line)
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
lsEntity ls_entity_convert_circle(const lsCircle *circle)
{
    lsEntity entity;
    entity.type = kCircle;
    entity.data.circle = *circle;
    return entity;
}

/**
 * @brief Convert lsArc to lsEntity
 * 
 * @param arc pointer to arc
 * @return lsEntity 
 */
lsEntity ls_entity_convert_arc(const lsArc *arc)
{
    lsEntity entity;
    entity.type = kArc;
    entity.data.arc = *arc;
    return entity;
}

/**
 * @brief Get the boundbox of the entity
 * 
 * @param entity 
 * @return lsBoundbox 
 */
lsBoundbox ls_entity_get_boundbox(const lsEntity *entity)
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

    case kArc:
        box = ls_arc_get_circle_boundbox(&entity->data.arc);
        break;

    default:
        break;
    }

    return box;
}

// 求一组实体的包围盒。属于C++函数重载还有引用的特性
lsBoundbox ls_entity_get_boundbox(const std::vector<lsEntity> &entitys)
{
    lsBoundbox ret = ls_boundbox_init();
    for (size_t i = 0; i < entitys.size(); ++i)
    {
        lsBoundbox box = ls_entity_get_boundbox(&entitys[i]);
        ret = ls_boundbox_combine(&ret, &box);
    }
    return ret;
}

lsEntity ls_entity_translate(const lsEntity *entity, const lsVector *vector)
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

    case kArc:
        ent.data.arc = ls_arc_translate(&entity->data.arc, vector);
        ent = ls_entity_convert_arc(&ent.data.arc);
        break;

    default:
        ent.type = kUnknown;
        break;
    }

    return ent;
}

/**
 * @brief 实体的坐标系变换。将实体的世界坐标转换到坐标系 \p cs 下的坐标表示。
 * 
 * @param entity 
 * @param cs 
 * @return lsEntity 
 */
lsEntity ls_entity_transform(const lsEntity *entity, const lsCoordSystem *cs)
{
    lsEntity ent;

    switch (entity->type)
    {
    case kLine:
        ent.data.line = ls_line_transform(&entity->data.line, cs);
        ent = ls_entity_convert_line(&ent.data.line);
        break;

    case kCircle:
        ent.data.circle = ls_circle_transform(&entity->data.circle, cs);
        ent = ls_entity_convert_circle(&ent.data.circle);
        break;

    case kArc:
        ent.data.arc = ls_arc_transform(&entity->data.arc, cs);
        ent = ls_entity_convert_arc(&ent.data.arc);
        break;

    default:
        ent.type = kUnknown;
        break;
    }

    return ent;
}
