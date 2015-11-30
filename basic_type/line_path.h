#ifndef __UML_BASIC_TYPE_LINE_PATH_TYPE_H__
#define __UML_BASIC_TYPE_LINE_PATH_TYPE_H__

#include "point.h"
#include "../single_list-template.h"
#include "../canvas.h"


typedef enum { 
    STRAIGHT_LINE,
    BEZIER_CURVE_LINE,
    ARC_LINE
} line_unit_type;

typedef struct _line_unit {
    line_unit_type type;
    int            pt_num;
} line_unit_t;


GENERAL_SLIST_MODULE_DEF(point)

GENERAL_SLIST_MODULE_DEF(line_unit)

typedef struct _line_path {
    SLIST(point) *pts;
    SLIST(line_unit) *line_units;
} line_path_t;

extern line_path_t *line_path_create (void);

extern void  line_path_add_pts (line_path_t *path,
        SLIST(point) *pts, line_unit_type type);

extern void line_path_paint (line_path_t *path, canvas_t *ca);

extern void line_path_destroy (line_path_t *path);

#endif
