#include "utils.h"
#include "object-private.h"
#include <string.h>

/*************************   class chain   **************************/

/********************************************************************
 * *** this part will call the component class mthod in class whose *
 * *** inherit object class. Please make sure you initial correctly.* 
 * *** these functions are called from component functions          *
 * ******************************************************************/

/**
 * paint - the componet class paint method in object class.
 *  and the behavior is bridge.
 * @co - the component object and it is also OBJECT_TYPE object
 * @ca - the canvas
 * */
static void paint (component_t *co, canvas_t *ca) {
    object_t *obj = co;
    component_class *_class = (component_class*)obj->priv->_class;
    _class->paint (co, ca);
}

/**
 * is_inside - the component class is_inside method in object class
 *  and the behavior is bridge.
 * @co - the component object and it is also OBJECT_TYPE object.
 * @pt - the point with position (x, y)
 * */
static int is_inside (component_t *co, point_t *pt) {
    object_t *obj = co;
    component_class *_class = obj->priv->_class;
    return _class->is_inside (co, pt);
}


/**
 * is_covered - the component class is_covered method in object class
 * and the behavior is bridge.
 * @co - the component object and it is also OBJECT_TYPE object.
 * @re - the rectangle range 
 * */
static int is_covered (component_t *co, rectangle_t *re) {
    object_t *obj = co;
    component_class *_class = obj->priv->_class;
    return _class->is_covered (co, re); 
}

/**
 * selected - the component class selected method in object class
 *  and the behavior is bridge.
 * @co - the component object and it is also OBJECT_TYPE object.
 * */
static void selected (component_t *co) {
    object_t *obj = co;
    xfunc_error_log("object selected!\n");
    ((component_class*)obj->priv->_class)->selected(co);
}

/**
 * unselected - the component class unselected method in object class
 *  and the behavior is bridge.
 * @co - the component object and it is also OBJECT_TYPE object.
 * */
static void unselected (component_t *co) {
    object_t *obj = co;
    
    xfunc_error_log("object unselected!\n");
    ((component_class*)obj->priv->_class)->unselected(co);
}

/**
 * destroy - release the resource of `co` and free the object private
 * data.
 * @co - the component object and it is also OBJECT_TYPE object.
 * */
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

/*********************** the end of class chain *****************************/

/**
 *
 * object protected part function
 *
 * */

/**
 * private_create - create object private part
 * @type - the type of OBJECT_TYPE component
 * @_class - the object class method of inherent class
 * 
 * @return - the object type private part that contain type , 
 *  position and inherent class
 * */
static object_private *private_create (object_type type, object_class *_class) {
    object_private *priv = xmalloc (sizeof (object_private));

    priv->type = type;
    priv->pos.x = 0;
    priv->pos.y = 0;

    priv->_class = _class;

    return priv;
}

/**
 * object_init_class - init `obj` for use object class method
 * @obj - the object you want ot initialize
 * @type - the TYPE of the obj should be
 * @_class - the inherent class method
 *
 * */
void object_init_class (object_t *obj,
        object_type type, object_class *_class) {
    component_init_class (obj, OBJECT_TYPE, &inherent_class);
    obj->priv = private_create (type, _class);
}

/*********************************************************************/

/**
 * 
 * the object public function
 *
 * Note. Some function will call the inherent class mthod.
 *  Please make sure the object initialized correctly.
 *
 * */

/**
 * object_update - update `obj` status
 * @obj - the object 
 *
 * */
void object_update (object_t *obj) {
    obj->priv->_class->update (obj);
}

/**
 * object_set_pos - the center postition of `obj`
 * @obj - the object
 * @pos - the position you want to set.
 *
 * */
void object_set_pos (object_t *obj, point_t *pos) {
    obj->priv->pos = *pos;
}


/**
 * object_get_pos - get the position of `obj`
 * @obj - the object
 * 
 * @return - the position address of `obj`.
 * */
const point_t *object_get_pos (object_t *obj) {
    return &obj->priv->pos;
}

/**
 * object_get_region - get the rectangle region of `obj`
 * @obj - the object
 *
 * @return - the rectangle address of `obj`.
 * */
const rectangle_t *object_get_region (object_t *obj) {
    return obj->priv->_class->get_region (obj);
}

/**
 * object_get_type - get the object type of `obj`
 * @obj - the object
 *
 * @return - the object type
 * */
object_type object_get_type (object_t *obj) {
    return obj->priv->type;
}
