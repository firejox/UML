#include "../../utils.h"
#include "composition_line-private.h"


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

void set_start_decorate (line_t *con, point_t *st, point_t *ed) {
    line_decorate_t *dec = line_get_start_decorate (con);
    double dist, width;
    point_t tmp;

    dist = hypot (st->x - ed->x, st->y - ed->y);

    width = line_decorate_get_width (dec) / 2;

    tmp.x = st->x * ((dist - width) / dist) + ed->x * (width / dist);

    tmp.y = st->y * ((dist - width) / dist) + ed->y * (width / dist);

    object_set_pos (dec, &tmp);

    line_decorate_set_angle (dec, atan2(st->x - ed->x, st->y - ed->y));

    st->x = tmp.x;
    st->y = tmp.y;

}

/****************   class chain   *********************/

static void update (line_t *con) {
    composition_line_t *g_con = con;
    port_object_t *pst, *ped;

    point_t st, ed, tmp;
    line_path_t *path;

    pst = line_get_start_object (con);
    ped = line_get_end_object   (con);

    if (pst == NULL || ped == NULL)
        return;

    port_object_get_absolute_pos (pst, &st);
    
    port_object_get_absolute_pos (ped, &ed);

    set_start_decorate (con, &st, &ed);
    
    path = path_create (&st, &ed);

    line_set_line_path (con, path); 
}


static line_class inherent_class = {
    .update = update
};

/****************************************************/

static composition_line_private *private_create(void) {
    return NULL;
}

static image_t *get_src_decorate_image(void) {
    static image_t *im = NULL;
    
    if (im)
        return im;

    return (im = image_create_from_resource ("/image/composition_line", 20, 20));
}

composition_line_t *generalization_line_create 
                    (port_object_t *st, port_object_t *ed) {
    composition_line_t *con = xmalloc (sizeof (composition_line_t));
    image_t *im = NULL;
    line_decorate_t *dec = NULL;

    line_init_class (con, &inherent_class);
    
    con->priv = private_create ();

    line_set_start_object (con, st);

    line_set_end_object (con, ed);

    im = get_src_decorate_image ();

    dec = line_decorate_create (im);

    line_set_start_decorate (con, dec);

    update (con);

    return con;
}

