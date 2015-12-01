#include "utils.h"

#include "component-private.h"

static component_private *private_create (
        component_type type,component_class *_class) {
    component_private *priv = xmalloc (sizeof (component_private));

    priv->type        = type;

    priv->is_selected = 0;

    priv->ref_count   = 0;

    priv->_class = _class;
    
    return priv;
}


void component_init_class (component_t *co,
        component_type type, component_class *_class) {
    if (co)
        co->priv = private_create (type, _class);
}

component_t *component_ref (component_t *co) {
    if (co) {
        xfunc_error_log ("%p ref_count :%d\n", co, co->priv->ref_count);
        co->priv->ref_count ++;
    }
    return co;   
}

void component_paint (component_t *co, canvas_t *ca) {
    if (co) {
        co->priv->_class->paint(co, ca);
    }
}

int is_component_inside (component_t *co, point_t *pt) {
    if (co)
        return co->priv->_class->is_inside (co, pt);
    return 0;
}

int is_component_covered (component_t *co, rectangle_t *re) {
    if (co)
        return co->priv->_class->is_covered (co, re);
    return 0;
}

component_type component_get_type (component_t *co) {
    if (co)
        return co->priv->type;
    return INVALID_TYPE;
}

void component_selected (component_t *co) {
    if (co) { 
        if (!co->priv->is_selected){
            co->priv->is_selected = 1;
            co->priv->_class->selected(co);
        }
    }
}

void component_unselected (component_t *co) {
    if (co) {
        if (co->priv->is_selected){
            co->priv->is_selected = 0;
            co->priv->_class->unselected(co);
        }
    }
}

int  component_get_selected (component_t *co) {
    if (co)
        return co->priv->is_selected;
    return 0;
}

void component_destroy (component_t *co) {

    if (co) {
        xfunc_error_log ("%p ref_count :%d\n", co, co->priv->ref_count);

        co->priv->ref_count --;
        if (co->priv->ref_count <= 0) {
            co->priv->_class->destroy(co);
            xfree(co->priv);
            xfree(co);
        }
    }
}
