#include "../../utils.h"
#include "association_line-private.h"
#include <string.h>



line_path_t *path_create (point_t *st, point_t *ed) {
    line_path_t *path = line_path_create ();
    SLIST(point) *pts = SLIST_CREATE(point)();
    SLIST_NODE(point) *nd;
    
    nd = SLIST_NODE_CREATE(point)(point_create (st->x, st->y));

    single_list_prepend (pts, nd);

    nd = SLIST_NODE_CREATE(point)(point_create (ed->x, ed->y));

    single_list_prepend (pts, nd);

    line_path_add_pts (path, pts, STRAIGHT_LINE);

    SLIST_DESTROY(point)(pts);

    return path;
}

/****************   class chain   *********************/

static void update (line_t *con) {
    association_line_t *a_con = con;
    port_object_t *pst, *ped;

    point_t st, ed;
    line_path_t *path;

    pst = line_get_start_object (con);
    ped = line_get_end_object   (con);

    if (pst == NULL || ped == NULL)
        return;

    port_object_get_absolute_pos (pst, &st);
    
    port_object_get_absolute_pos (ped, &ed);
    
    path = path_create (&st, &ed);

    line_set_line_path (con, path); 
}


static line_class inherent_class = {
    .update = update
};

/****************************************************/


static association_line_private *private_create(void) {
    return NULL;
}

association_line_t *association_line_create 
                    (port_object_t *st, port_object_t *ed) {
    association_line_t *con = xmalloc (sizeof (association_line_t));

    line_init_class (con, &inherent_class);
    
    con->priv = private_create ();

    line_set_start_object (con, st);

    line_set_end_object (con, ed);

    update (con);

    return con;
}
