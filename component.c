#include "utils.h"

#include "component-private.h"

static component_private *private_create (
        component_type type,component_class *_class) {
    component_private *priv = xmalloc (sizeof (component_private));

    priv->type        = type;

    priv->is_selected = 0;

    priv->is_dirty    = 0;

    priv->_class = _class;
    
    return priv;
}


void component_init_class (component_t *co,
        component_type type, component_class *_class) {
    co->priv = private_create (type, _class);
}

void component_mark_dirty (component_t *co) {
    co->priv->is_dirty = 1;
}

void component_paint (component_t *co, canvas_t *ca) {
    if (co->priv->is_dirty) {
        co->priv->is_dirty = 0;
        co->priv->_class->paint(co, ca);
    }
}

int is_component_inside (component_t *co, point_t *pt) {
    return co->priv->_class->is_inside (co, pt);
}

int is_component_covered (component_t *co, rectangle_t *re) {
    return co->priv->_class->is_covered (co, re);
}

component_type component_get_type (component_t *co) {
    return co->priv->type;
}

void component_selected (component_t *co) {
    co->priv->is_selected = 1;
    co->priv->_class->selected (co);
}

void component_unselected (component_t *co) {
    co->priv->is_selected = 0;
    co->priv->_class->unselected (co);
}

int  component_get_selected (component_t *co) {
    return co->priv->is_selected;
}

void component_destory (component_t *co) {
    co->priv->_class->destory(co);
    xfree(co->priv);
    xfree(co);
}
