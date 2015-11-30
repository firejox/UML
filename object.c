#include "utils.h"
#include "object-private.h"
#include <string.h>

/****************   class chain   *********************/
static void paint (component_t *co, canvas_t *ca) {
    object_t *obj = co;
    component_class *_class = (component_class*)obj->priv->_class;
    _class->paint (co, ca);
}

static int is_inside (component_t *co, point_t *pt) {
    object_t *obj = co;
    component_class *_class = obj->priv->_class;
    return _class->is_inside (co, pt);
}

static int is_covered (component_t *co, rectangle_t *re) {
    object_t *obj = co;
    component_class *_class = obj->priv->_class;
    return _class->is_covered (co, re); 
}

static void selected (component_t *co) {
    object_t *obj = co;
    xfunc_error_log("object selected!\n");
    ((component_class*)obj->priv->_class)->selected(co);
}

static void unselected (component_t *co) {
    object_t *obj = co;
    
    xfunc_error_log("object unselected!\n");
    ((component_class*)obj->priv->_class)->unselected(co);
}

static void destroy (component_t *co) {
    object_t *obj = co;
    component_class *_class = obj->priv->_class;
    _class->destroy (co);
    xfree (obj->priv);
}


static component_class inherent_class = {
    .paint      = paint,
    .is_inside  = is_inside,
    .is_covered = is_covered,
    .selected   = selected,
    .unselected = unselected,
    .destroy    = destroy
};


static object_private *private_create (object_type type, object_class *_class) {
    object_private *priv = xmalloc (sizeof (object_private));

    priv->type = type;
    priv->pos.x = 0;
    priv->pos.y = 0;

    priv->_class = _class;

    return priv;
}


void object_init_class (object_t *obj,
        object_type type, object_class *_class) {
    component_init_class (obj, OBJECT_TYPE, &inherent_class);
    obj->priv = private_create (type, _class);
}

/******************************************************/

void object_update (object_t *obj) {
    obj->priv->_class->update (obj);
}

void object_set_pos (object_t *obj, point_t *pos) {
    obj->priv->pos = *pos;
}

const point_t *object_get_pos (object_t *obj) {
    return &obj->priv->pos;
}

const rectangle_t *object_get_region (object_t *obj) {
    return obj->priv->_class->get_region (obj);
}

object_type object_get_type (object_t *obj) {
    return obj->priv->type;
}
