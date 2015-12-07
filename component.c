#include "utils.h"

#include "component-private.h"

/**
 * private_create - create component private part
 * @type - the type of component
 * @_class - the component class method of inherent class
 *
 * @return - the component private part that contain type,
 *  is_selected, reference count, state of select 
 *  and inherent class information.
 * */
static component_private *private_create (
        component_type type,component_class *_class) {
    component_private *priv = xmalloc (sizeof (component_private));

    priv->type        = type;

    priv->is_selected = 0;

    priv->ref_count   = 0;

    priv->_class = _class;
    
    return priv;
}


/**
 * component_init_class - init `co` for use component class method
 * @co - the object you want to initialize
 * @type - the component type of `co`
 *
 * Note. any inherent component_class object should call it at create time
 * */
void component_init_class (component_t *co,
        component_type type, component_class *_class) {
    if (co)
        co->priv = private_create (type, _class);
}


/**
 * component_ref - increase the reference count of `co`
 * @co - the component object
 * 
 * @return - `co` the component object.
 * ********************************************************
 * *** If you pass NULL then it would return NULL, you ****
 * *** should check by yourself.                       ****
 * ********************************************************
 * */
component_t *component_ref (component_t *co) {
    if (co) {
        xfunc_error_log ("%p ref_count :%d\n", co, co->priv->ref_count);
        co->priv->ref_count ++;
    }
    return co;   
}

/****************************************************************
 * The below part would call the inherent class method.         *
 * So please make sure you intialize the class method correctly,*
 * before you want ot call these functions.                     *
 ****************************************************************/


/**
 * component_paint - paint `co` onto the `ca`
 * @co - the component object
 * @ca - the canavs object 
 * */
void component_paint (component_t *co, canvas_t *ca) {
    if (co) {
        co->priv->_class->paint(co, ca);
    }
}

/**
 * is_component_inside - check the point `pt` whether inside
 *  the `co`
 * @co - the component object
 * @pt - the point with the position (x, y)
 * 
 * @return - If it is true then return non-zero ,
 *  and return zero if not.
 * */
int is_component_inside (component_t *co, point_t *pt) {
    if (co)
        return co->priv->_class->is_inside (co, pt);
    return 0;
}


/**
 * is_component_covered - check the rectangle `re` whether 
 *  cover `co`
 * @co - component object
 * @re - the rectangle range
 * 
 * @return -If it is ture the return non-zero, 
 *  and return zero if not.
 * */
int is_component_covered (component_t *co, rectangle_t *re) {
    if (co)
        return co->priv->_class->is_covered (co, re);
    return 0;
}


/**
 * component_get_type - get the component type of `co`
 * @co - the component object
 *
 * @return - the component type of `co`, if you pass NULL
 * then will obtain the INVAILD_TYPE.
 * */
component_type component_get_type (component_t *co) {
    if (co)
        return co->priv->type;
    return INVALID_TYPE;
}


/**
 * component_selected - mark `co` selected
 * @co - the component object
 * */
void component_selected (component_t *co) {
    if (co) { 
        if (!co->priv->is_selected){
            co->priv->is_selected = 1;
            co->priv->_class->selected(co);
        }
    }
}


/**
 * component_unselected - mark `co` unselected
 * @co - the component object
 * */
void component_unselected (component_t *co) {
    if (co) {
        if (co->priv->is_selected){
            co->priv->is_selected = 0;
            co->priv->_class->unselected(co);
        }
    }
}


/**
 * component_get_selected - get the selected state of `co`
 * @co - the component object
 *
 * @return - if `co` is selected the return non-zero, 
 *  and return zero if not.
 * */
int component_get_selected (component_t *co) {
    if (co)
        return co->priv->is_selected;
    return 0;
}


/**
 * component_destroy - decreasing the reference count by one.
 *  if the result is less than or equal to zero, then release the 
 *  resource of `co`.
 *  @co - the component object
 *
 * */
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
