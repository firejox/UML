#ifndef __UML_LINE_PRIVATE_H__
#define __UML_LINE_PRIVATE_H__

#include "basic_types.h"


#include "line-protected.h"
#include "component-protected.h"


struct _line_private {
    line_path_t     *path;

    line_decorate_t *st_dec;
    line_decorate_t *ed_dec;

    port_object_t   *st_port;
    port_object_t   *ed_port;

    unsigned int    paint_flag:1;

    line_class      *_class;
};


#endif
