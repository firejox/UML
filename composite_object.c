#include "utils.h"
#include "object-protected.h"
#include "composite_object.h"
#include <math.h>

struct _composite_object_private {
    general_object_pool_t *pool;
    rectangle_t           rect;
};

/****************   class chain   *********************/

/***************  component class ********************/
static void paint (component_t *co, canvas_t *ca) {
    composite_object_t *com = co;
    general_object_unit_t *p;


    for_each_node_in_double_list_reverse(p, com->priv->pool) {
        component_paint(GO_UNIT_GET_COMPONENT(p), ca);
    }

    cairo_save (ca->cr);
    
    cairo_set_source_rgba (ca->cr, 0.5, 0.5, 1.0, 1.0);

    rectangle_paint (&com->priv->rect, ca);
    
    cairo_set_source_rgba (ca->cr, 0.0, 0.0, 0.0, 1.0);

    cairo_fill (ca->cr);

    cairo_restore (ca->cr);

}

static int is_inside (component_t *co, point_t *pt) { 
    composite_object_t *com = co;

    return is_rectangle_inside (&com->priv->rect, pt); 
}

static int is_covered (component_t *co, rectangle_t *re) {
    composite_object_t *com = co;

    return is_rectangle_covered (&com->priv->rect, re); 
}

static void selected (component_t *co) {
    composite_object_t *com = co;
    general_object_unit_t *p;

    for_each_node_in_double_list(p, com->priv->pool) {
        component_selected (GO_UNIT_GET_COMPONENT(p));
    }
}

static void unselected (component_t *co) {
    composite_object_t *com = co;
    general_object_unit_t *p;

    for_each_node_in_double_list(p, com->priv->pool) {
        component_unselected (GO_UNIT_GET_COMPONENT(p));
    }
}

static void destroy (component_t *co) {
    composite_object_t *com = co;

    general_object_pool_destroy(com->priv->pool);

    xfree (com->priv);
}

/*************   object class   *******************/

static void update (object_t *obj) {
    composite_object_t *com = obj;
    
    const point_t *obj_pos = NULL;
    point_t offset, tmp;

    general_object_unit_t *p;
    component_t *data;

    obj_pos = object_get_pos (com);

    if (!is_same_point(&com->priv->rect.center, obj_pos)) {
        offset.x = obj_pos->x - com->priv->rect.center.x;
        offset.y = obj_pos->y - com->priv->rect.center.y;

        com->priv->rect.center = *obj_pos;

        for_each_node_in_double_list(p, com->priv->pool) {
            data = GO_UNIT_GET_COMPONENT(p);

            obj_pos = object_get_pos (data);

            tmp.x = obj_pos->x + offset.x;
            tmp.y = obj_pos->y + offset.y;

            object_set_pos (data, &tmp);

            object_update (data);
        }
    }
}

static const rectangle_t *get_region (object_t *obj) {
    composite_object_t *com = obj;

    return &com->priv->rect;
}


static object_class inherent_class = 
{
    .p_class = {
        .paint      = paint,
        .is_inside  = is_inside,
        .is_covered = is_covered,
        .selected   = selected,
        .unselected = unselected,
        .destroy    = destroy
    },
    .update = update,
    .get_region = get_region
};

/***************************************************/


static composite_object_private *private_create (general_object_pool_t *pool) {
    composite_object_private *priv = xmalloc(sizeof(composite_object_private));

    general_object_unit_t *p;
    const rectangle_t *re;

    point_t top_left = {NAN, NAN}, bot_right = {NAN, NAN};
    double width;

    priv->pool = pool;

    for_each_node_in_double_list(p, pool) {
        re = object_get_region ((object_t*)GO_UNIT_GET_COMPONENT(p));

        if (re) {
            top_left.x = fmin (top_left.x, re->center.x - (re->width / 2.0));
            top_left.y = fmin (top_left.y, re->center.y - (re->height / 2.0));

            bot_right.x = fmax (bot_right.x, re->center.x + (re->width / 2.0));
            bot_right.x = fmax (bot_right.x, re->center.x + (re->height / 2.0));
        }
    }

    width = fmax (bot_right.x - top_left.x, bot_right.y - top_left.y);

    priv->rect.center.x = (top_left.x + bot_right.x) / 2.0;
    priv->rect.center.y = (top_left.y + bot_right.y) / 2.0;

    priv->rect.width = width;
    priv->rect.height = width;

    return priv;
}



composite_object_t *composite_object_group (general_object_pool_t *pool) {
    composite_object_t *com = xmalloc (sizeof (composite_object_t));
    
    object_init_class (com, COMPOSITE_OBJECT_TYPE, &inherent_class);

    com->priv = private_create (pool);
    
    return com;
}

general_object_pool_t *composite_object_ungroup (composite_object_t *com) {
    general_object_pool_t *pool = com->priv->pool;
    com->priv->pool = NULL;
    component_destroy (com);

    return pool;
}
