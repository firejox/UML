#include "line-private.h"


/****************   class chain   *********************/
static void paint (component_t *co, canvas_t *ca) {
    line_t *con = co;
    
}

static void selected (component_t *co) {}

static void unselected (component_t *co) {}

static int is_inside (component_t *co, point_t *pt) { return 0; }

static int is_covered (component_t *co, point_t *pt) { return 0; }

static void destory (component_t *co) {
    line_t *con = co;
    if (!con->priv->ref_count) {
        component_destory (con->priv->st_dec);
        component_destory (con->priv->ed_dec);
        line_path_destory (con->priv->path);
        xfree (con->priv);
    } else 
        con->priv->ref_count--;
}


static component_class line_class = {
    .paint      = paint,
    .selected   = selected,
    .unselected = unselected,
    .is_inside  = is_inside,
    .is_covered = is_covered,
    .destory    = destory
};

static line_private *private_create (line_class *_class) {
    line_private *priv = xmalloc (sizeof (line_private));

}

void line_init_class (line_t *con, line_class *_class) {
    

}


/****************************************************/

line_t *line_ref (line_t *con) {
    con->ref_count ++;
    return con;
}

void line_update (line_t *con) {
    con->priv->_class->update (con);
    component_mark_dirty (con);
}

void line_set_start_object (line_t *con, port_object_t *port) {
    con->priv->st_port = port_object_ref (port);
}

void line_set_end_object (line_t *con, port_object_t *port) {
    con->priv->ed_port = port_object_ref (port);
}


