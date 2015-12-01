#include "line-private.h"
#include "utils.h"
#include <assert.h>


/****************   class chain   *********************/


static void paint (component_t *co, canvas_t *ca) {
    line_t *con = co;
    port_object_t *st_port = con->priv->st_port;
    port_object_t *ed_port = con->priv->ed_port;

    if (con->priv->paint_flag || st_port == NULL) {
        line_path_paint (con->priv->path  , ca);
        component_paint (con->priv->st_dec, ca);
        component_paint (con->priv->ed_dec, ca);
    }

    con->priv->paint_flag = ~(con->priv->paint_flag);   
}

static int is_inside (component_t *co, point_t *pt) { return 0; }

static int is_covered (component_t *co, rectangle_t *re) { return 0; }

static void destroy (component_t *co) {
    line_t *con = co;
    if (!con->priv->ref_count) {
        component_destroy (con->priv->st_dec);
        component_destroy (con->priv->ed_dec);
        line_path_destroy (con->priv->path);
        xfree (con->priv);
    } else {
        port_object_unlink_line (con->priv->st_port, con);
        port_object_unlink_line (con->priv->ed_port, con);    
        con->priv->ref_count--;
    }
}


static component_class inherent_class = {
    .paint      = paint,
    .is_inside  = is_inside,
    .is_covered = is_covered,
    .destroy    = destroy
};


/****************************************************/

static line_private *private_create (line_class *_class) {
    line_private *priv = xmalloc (sizeof (line_private));

    priv->path       = NULL;

    priv->st_dec     = NULL;
    priv->ed_dec     = NULL;

    priv->st_port    = NULL;
    priv->ed_port    = NULL;

    priv->ref_count  = 0;

    priv->paint_flag = 1; 

    priv->_class = _class;

    return priv;
}

void line_init_class (line_t *con, line_class *_class) {
   component_init_class ((component_t*)con, LINE_TYPE, &inherent_class);

   con->priv = private_create(_class);

}

void line_set_line_path (line_t *con, line_path_t *p) {
    if (con->priv->path)
        line_path_destroy (con->priv->path);
    con->priv->path = p;
}

void line_set_start_decorate (line_t *con, line_decorate_t *dec) {
    if (con->priv->st_dec)
        component_destroy (con->priv->st_dec);
    con->priv->st_dec = dec;
}

void line_set_end_decorate (line_t *con, line_decorate_t *dec) {
    if (con->priv->ed_dec)
        component_destroy (con->priv->ed_dec);
    con->priv->ed_dec = dec;
}


line_decorate_t *line_get_start_decorate (line_t *con) {
    return con->priv->st_dec;
}

line_decorate_t *line_get_end_decorate (line_t *con) {
    return con->priv->ed_dec;
}

/*********************************************************/


line_t *line_ref (line_t *con) {
    con->priv->ref_count ++;
    return con;
}

void line_update (line_t *con) {
    con->priv->_class->update (con);
}

void line_set_start_object (line_t *con, port_object_t *port) {
    con->priv->st_port = port;
}

void line_set_end_object (line_t *con, port_object_t *port) {
    con->priv->ed_port = port;
}

const port_object_t *line_get_start_object (line_t *con) {
    return con->priv->st_port;  
}

const port_object_t *line_get_end_object (line_t *con) {
    return con->priv->ed_port;
}
