
#include "utils.h"
#include "port_object.h"
#include "object-protected.h"

#include "single_list-template.h"

GENERAL_SLIST_MODULE_DEF(line)
GENERAL_SLIST_MODULE_IMPL(line, component_destroy);

#define PORT_OBJECT_WIDTH  10
#define PORT_OBJECT_HEIGHT PORT_OBJECT_WIDTH

struct _port_object_private {
    basic_object_t *src_obj;
    rectangle_t    range;
    SLIST(line)    *cons;
};



/****************   class chain   *********************/

/***************  component class ********************/
static void paint (component_t *co, canvas_t *ca) {
    port_object_t *port = co;
    const point_t *pt = NULL;
    SLIST_NODE(line) *p = NULL;
    


    cairo_save (ca->cr);

    for_each_node_in_single_list(p, port->priv->cons) {
        component_paint(p->data, ca);
    }

    pt = object_get_pos (port->priv->src_obj);

    cairo_translate (ca->cr, pt->x, pt->y);

    pt = object_get_pos (port);

    if (component_get_selected (port)) {
    
        cairo_set_source_rgb(ca->cr, 0.0, 0.0, 0.0);

        rectangle_paint (&port->priv->range, ca);

        cairo_fill (ca->cr);
    }
    
    cairo_restore (ca->cr);

}

static int is_inside (component_t *co, point_t *pt) { return 0; }

static int is_covered (component_t *co, rectangle_t *re) { return 0; }

static void selected (component_t *co) { 
    xfunc_error_log ("port object selected!\n");
}

static void unselected (component_t *co) { 
    xfunc_error_log ("port object unselected!\n");

}

static void destroy (component_t *co) {
    port_object_t *port = co;
    SLIST_NODE(line) *p;

    SLIST_DESTROY(line)(port->priv->cons);

    xfree (port->priv);
}

/*************   object class   *******************/
static void update (object_t *obj) {
    port_object_t *port = obj;
    SLIST_NODE(line) *p;
    const point_t *pt = object_get_pos (obj);

    port->priv->range.center.x = pt->x;
    port->priv->range.center.y = pt->y;
    

    for_each_node_in_single_list(p, port->priv->cons) 
        line_update (p->data);
}

static const rectangle_t *get_region (object_t *obj) {
    port_object_t *port = obj;

    return &port->priv->range;
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

static port_object_private *private_create (basic_object_t *obj, point_t *pt) {
    port_object_private *pri = xmalloc (sizeof (port_object_private));

    pri->src_obj = obj;
    pri->cons = SLIST_CREATE(line)();
    pri->range.center.x = pt->x;
    pri->range.center.y = pt->y;

    pri->range.width  = PORT_OBJECT_WIDTH;
    pri->range.height = PORT_OBJECT_HEIGHT;


    return pri;
}

port_object_t *port_object_create (basic_object_t *obj, point_t *pt) {
    port_object_t *port = xmalloc (sizeof (port_object_t));

    port->priv = private_create (obj, pt);

    object_init_class (port, PORT_OBJECT_TYPE, &inherent_class);
    
    object_set_pos (port, pt);

    return port;
}


void port_object_link_line (port_object_t *port, line_t *con) {
    SLIST_NODE(line) *nd;

    con = (line_t*)component_ref (con);
    nd = SLIST_NODE_CREATE(line)(con);

    single_list_prepend(port->priv->cons, nd);
}

void port_object_unlink_line (port_object_t *port, line_t *con) {
    SLIST_NODE(line) *p = NULL, *q = NULL;

    for_each_node_in_single_list (p, port->priv->cons) {
        if (p->data == con)
            break;
        q = p;
    }

    if (p != NULL) {
        if (q == NULL) 
            port->priv->cons->head = p->next;
        else 
            q->next = p->next;

        SLIST_NODE_DESTROY(line)(p);
    }
}

void port_object_get_absolute_pos (port_object_t *port, point_t *pos) {
    const point_t *p_pt = object_get_pos (port);
    const point_t *o_pt = object_get_pos (port->priv->src_obj);

    pos->x = o_pt->x + p_pt->x;
    pos->y = o_pt->y + p_pt->y;
}

basic_object_t *port_object_get_basic_object (port_object_t *port) {
    return port->priv->src_obj;
}
