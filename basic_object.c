#include "utils.h"
#include "basic_object-private.h"
#include <math.h>

GENERAL_SLIST_MODULE_IMPL(port_object, component_destroy)

/****************   class chain   *********************/

/***************  component class ********************/
static void paint (component_t *co, canvas_t *ca) {
    basic_object_t *obj = co;
    SLIST_NODE(port_object) *p;

    ((component_class*)obj->priv->_class)->paint(co, ca);

    for_each_node_in_single_list(p, obj->priv->ports)
        component_paint (p->data, ca);
}

static int is_inside (component_t *co, point_t *pt) { 
    basic_object_t *obj = co;

    return ((component_class*)obj->priv->_class)->is_inside(co, pt); 
}

static int is_covered (component_t *co, rectangle_t *re) {
    basic_object_t *obj = co;

    return ((component_class*)obj->priv->_class)->is_covered(co, re); 
}

static void selected (component_t *co) {
    basic_object_t *obj = co;
    SLIST_NODE(port_object) *p;

    for_each_node_in_single_list(p, obj->priv->ports) 
        component_selected (p->data);
}

static void unselected (component_t *co) {
    basic_object_t *obj = co;
    SLIST_NODE(port_object) *p;

    for_each_node_in_single_list(p, obj->priv->ports)
        component_unselected (p->data);
}

static void destroy (component_t *co) {
    basic_object_t *obj = co;
    ((component_class*)obj->priv->_class)->destroy(co);
    
    SLIST_DESTROY(port_object)(obj->priv->ports);

    xfree (obj->priv);
}

/*************   object class   *******************/

static void update (object_t *obj) {
    basic_object_t *b_obj = obj;
    SLIST_NODE(port_object) *p;

    const rectangle_t *range;
    point_t top_left, bot_right, real_pos;

    ((object_class*)b_obj->priv->_class)->update(obj);

    /**************** get base shape range *********************/

    range = ((object_class*)b_obj->priv->_class)->get_region(obj);

    top_left = (point_t) {
        .x = range->center.x - range->width / 2,
        .y = range->center.y - range->height / 2
    };

    bot_right = (point_t) {
        .x = range->center.x + range->width / 2,
        .y = range->center.y + range->height / 2
    };

    /***************** update port object *************************/

    for_each_node_in_single_list (p, b_obj->priv->ports) {
        object_update (p->data);

        range = object_get_region (p->data);
        port_object_get_absolute_pos (p->data, &real_pos);

        top_left.x = fmin (top_left.x, real_pos.x - range->width / 2);
        top_left.y = fmin (top_left.y, real_pos.y - range->height / 2);

        bot_right.x = fmax (bot_right.x, real_pos.x + range->width / 2);
        bot_right.y = fmax (bot_right.y, real_pos.y + range->height / 2);

    }

    b_obj->priv->range.width = bot_right.x - top_left.x;
    b_obj->priv->range.height = bot_right.y - top_left.y;

    b_obj->priv->range.center = (point_t) {
        .x = (bot_right.x + top_left.x) / 2,
        .y = (bot_right.y + top_left.y) / 2
    };
}

static const rectangle_t *get_region (object_t *obj) {
    basic_object_t *b_obj = obj;

    return &b_obj->priv->range;
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

static basic_object_private *private_create (basic_object_class *_class) {
    basic_object_private *priv = xmalloc (sizeof (basic_object_private));

    priv->ports = SLIST_CREATE(port_object)();
    priv->name = xstring_create();
    priv->_class = _class;

    
    return priv;
}

void basic_object_init_class (basic_object_t *obj, basic_object_class *_class) {
    object_init_class (obj, BASIC_OBJECT_TYPE, &inherent_class);
    obj->priv = private_create (_class);
}

void basic_object_add_port (basic_object_t *obj, port_object_t *port) {
    SLIST_NODE(port_object) *nd = SLIST_NODE_CREATE(port_object)(port);
    single_list_prepend (obj->priv->ports, nd);
}

SLIST(port_object) *basic_object_get_ports (basic_object_t *obj) {
    return obj->priv->ports;
}


void basic_object_set_name (basic_object_t *obj, const char *name) {
    xstring_set_string(obj->priv->name, name);
}

const char *basic_object_get_name (basic_object_t *obj) {
    return xstring_get_string (obj->priv->name);
}

port_object_t *basic_object_get_port_object 
                        (basic_object_t *obj, point_t *pos) {
    return obj->priv->_class->get_port_object (obj, pos);             
}
