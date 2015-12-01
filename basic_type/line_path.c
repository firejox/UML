#include "../utils.h"
#include "line_path.h"


line_unit_t *line_unit_create (int num, line_unit_type type) {
    line_unit_t *tmp = xmalloc (sizeof(line_unit_t));
    tmp->pt_num = num;
    tmp->type = type;
    return tmp;
}

void line_unit_destroy (line_unit_t *unit) {
    xfree (unit);
}

GENERAL_SLIST_MODULE_IMPL(point, point_destroy)
GENERAL_SLIST_MODULE_IMPL(line_unit, line_unit_destroy)

line_path_t *line_path_create(void) {
    line_path_t *tmp = xmalloc (sizeof(line_path_t));
    tmp->pts = SLIST_CREATE(point)();
    tmp->line_units = SLIST_CREATE(line_unit)();

    return tmp;
}

void line_path_add_pts (line_path_t *path,
        SLIST(point) *pts, line_unit_type type) {
    int num = 0;
    SLIST_NODE(point) *p, *q = NULL;
    SLIST_NODE(line_unit) *unit_nd;
    line_unit_t *unit;
    
    for_each_node_in_single_list (p, pts) {
        if (q) 
            single_list_prepend (path->pts, q);
        q = p;
        num ++;
    }
    
    if (q) {
        pts->head = NULL;
        single_list_prepend (path->pts, q);

        unit = line_unit_create (num, type);
        unit_nd = SLIST_NODE_CREATE(line_unit)(unit);
        
        single_list_prepend (path->line_units, unit_nd);
    }

}


/*
 * now only support straight line paint
 * discard the line type
 * */
void line_path_paint (line_path_t *path, canvas_t *ca) {
    SLIST_NODE(point) *p, *q = NULL;


    cairo_save (ca->cr);

    cairo_set_source_rgb (ca->cr, 0.0, 0.0, 0.0);

    cairo_set_line_width (ca->cr, 3.0);

    for_each_node_in_single_list(p, path->pts) {
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
    SLIST_DESTROY(point)(path->pts);
    SLIST_DESTROY(line_unit)(path->line_units);
    xfree(path);

}
