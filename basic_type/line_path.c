#include "../utils.h"
#include "line_path.h"


inline line_unit_t *line_unit_create (int num, line_unit_type type) {
    line_unit_t *tmp = xmalloc (sizeof(line_unit_t));
    tmp->num = num;
    tmp->type = type;
    return tmp;
}

inline void line_unit_destory (line_unit_t *unit) {
    xfree (unit);
}

GENERAL_SLIST_MODULE_IMPL(point, point_destory)
GENERAL_SLIST_MODULE_IMPL(line_unit, line_unit_destory)

inline line_path_t *line_path_create(void) {
    line_path_t *tmp = xmalloc (sizeof(line_path_t));
    tmp->pts = SLIST_CREATE(point)();
    tmp->line_units = SLIST_CREATE(line_unit)();

    return tmp;
}

inline void line_path_add_pts (line_path_t *path,
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
    
    if (!num) {
        pts->head = NULL;
        single_list_prepend (path->pts, q);

        unit = line_path_create (num, type);
        unit_nd = SLIST_NODE_CREATE(line_unit)(unit);
        
        single_list_prepend (path->line_units, unit_nd);
    }

}


inline void line_path_destory (line_path_t *path) {
    SLIST_DESTORY(point)(path->pts);
    SLIST_DESTORY(line_unit)(path->line_units);
    xfree(path);

}
