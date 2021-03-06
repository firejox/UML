#ifndef __UML_LINE_PROTECTED_H__
#define __UML_LINE_PROTECTED_H__

#include "line.h"

extern void line_init_class (line_t *con, line_class *_class);

extern void line_set_line_path (line_t *con, line_path_t *p);

extern void line_set_start_decorate (line_t *con, line_decorate_t *dec);
extern void line_set_end_decorate   (line_t *con, line_decorate_t *dec);

extern line_decorate_t *line_get_start_decorate (line_t *con);
extern line_decorate_t *line_get_end_decorate   (line_t *con);
#endif
