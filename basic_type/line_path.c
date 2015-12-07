#include "../utils.h"
#include "line_path.h"


static line_unit_t *line_unit_create (int num, line_unit_type type) {
    line_unit_t *tmp = xmalloc (sizeof(line_unit_t));
    tmp->pt_num = num;
    tmp->type = type;
    return tmp;
}

void line_unit_destroy (line_unit_t *unit) {
    xfree (unit);
}

GENERAL_DLIST_MODULE_IMPL(line_unit, line_unit_destroy)

line_path_t *line_path_create(void) {
    line_path_t *tmp = xmalloc (sizeof(line_path_t));
    tmp->pts = point_list_create();
    tmp->line_units = DLIST_CREATE(line_unit)();

    return tmp;
}

void line_path_add_pts (line_path_t *path,
        point_list_t *pts, line_unit_type type) {
    int num = 0;
    point_unit_t *p;
    
    for_each_point_unit_in_point_list (p, pts) 
        num ++;
    
    if (num) {
        point_list_append_list(path->pts, pts);

        DLIST_APPEND_DATA(line_unit)(path->line_units,
                line_unit_create(num, type));
    }

}


/*
 * now only support straight line paint
 * discard the line type
 * */
void line_path_paint (line_path_t *path, canvas_t *ca) {
    point_unit_t *p, *q = NULL;


    cairo_save (ca->cr);

    cairo_set_source_rgb (ca->cr, 0.0, 0.0, 0.0);

    cairo_set_line_width (ca->cr, 3.0);

    for_each_point_unit_in_point_list(p, path->pts) {
        if (q) {
            cairo_move_to (ca->cr, q->data->x, q->data->y);
            cairo_line_to (ca->cr, p->data->x, p->data->y);
        }
        q = p;
    }

    cairo_stroke (ca->cr);

    cairo_restore (ca->cr);

}

void line_path_destroy (line_path_t *path) {
    point_list_destory(path->pts);
    DLIST_DESTROY(line_unit)(path->line_units);
    xfree(path);

}
