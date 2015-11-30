#ifndef __UML_MEOW_COMPOSITION_LINE_PRIVATE_H__
#define __UML_MEOW_COMPOSITION_LINE_PRIVATE_H__

#include "composition_line.h"
#include "../../line-protected.h"

struct _composition_line_private {};


extern line_path_t *path_create (point_t *st, point_t *ed);
extern void set_start_decorate (line_t *con, point_t *st, point_t *ed);
#endif
