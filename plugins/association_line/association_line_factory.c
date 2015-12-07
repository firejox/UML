#include "../../utils.h"
#include "association_line_factory.h"


static line_path_t *path_create (point_t *st, point_t *ed) {
    line_path_t *path = line_path_create ();
    point_list_t *pts = point_list_create();
    
    point_list_append_point (pts, point_create (st->x, st->y));

    point_list_append_point (pts, point_create (ed->x, ed->y));

    line_path_add_pts (path, pts, STRAIGHT_LINE);

    point_list_destory (pts);

    return path;
}

static line_factory_class fact_class = {
    .prod_class = {
        .path_create = path_create
    }
};


line_factory_t *association_line_factory_create (void) {

    return line_factory_create(&fact_class);
}
