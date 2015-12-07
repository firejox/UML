#include "../../utils.h"
#include "composition_line_factory.h"

#include <math.h>

static void start_decorate_update (line_decorate_t *dec, line_path_t *path) {
    double dist, width;
    point_unit_t *pu = path->pts->head;
    point_t tmp;
    point_t *st = pu->data;
    point_t *ed = (pu->next) ? pu->next->data : pu->data;

    dist = hypot (st->x - ed->x, st->y - ed->y);

    width = line_decorate_get_width (dec) / 2;

    tmp.x = st->x * ((dist - width) / dist) + ed->x * (width / dist);

    tmp.y = st->y * ((dist - width) / dist) + ed->y * (width / dist);

    object_set_pos (dec, &tmp);

    line_decorate_set_angle (dec, atan2(ed->y - st->y, ed->x - st->x));
    
    width = line_decorate_get_width (dec) - 2;

    tmp.x = st->x * ((dist - width) / dist) + ed->x * (width / dist);

    tmp.y = st->y * ((dist - width) / dist) + ed->y * (width / dist);

    *st = tmp;   
}

static line_path_t *path_create (point_t *st, point_t *ed) {
    line_path_t *path = line_path_create ();
    point_list_t *pts = point_list_create();
    
    point_list_append_point (pts, point_create (st->x, st->y));

    point_list_append_point (pts, point_create (ed->x, ed->y));

    line_path_add_pts (path, pts, STRAIGHT_LINE);

    point_list_destory (pts);

    return path;
}

static image_t *get_start_decorate_image(void) {
    static image_t *im = NULL;
    
    if (im)
        return im;

    return (im = image_create_from_resource 
            ("/line_decorate/composition_line", 25, 25));
}

static line_factory_class fact_class = {
    .prod_class = {
        .path_create = path_create,
        .start_decorate_update = start_decorate_update
    },
    .get_start_decorate_image = get_start_decorate_image
};

line_factory_t *composition_line_factory_create (void) {

    return line_factory_create(&fact_class);
}
