#ifndef __UML_MEOW_LINE_FACTORY_H__
#define __UML_MEOW_LINE_FACTORY_H__


typedef struct _line_factory line_factory_t;
typedef struct _line_factory_class line_factory_class;
typedef struct _line_factory_private line_factory_private;

#include "line.h"

struct _line_factory {
    line_factory_private *priv;
};

struct _line_factory_class {
    line_class prod_class;

    image_t *(* const get_start_decorate_image) (void);
    image_t *(* const get_end_decorate_image)   (void); 
};


extern line_factory_t *line_factory_create (line_factory_class *_class);

extern void line_factory_register_start_port 
                            (line_factory_t *fact, port_object_t *port);
extern void line_factory_register_end_port
                            (line_factory_t *fact, port_object_t *port);

/**
 *  This only work on `end port` having not registered and 
 *   `start port` having registered.
 * */
extern void line_factory_setup_end_pos
                            (line_factory_t *fact, point_t *pos);

extern line_t *line_factory_get_sample (line_factory_t *fact);

extern void line_factory_produce_one (line_factory_t *fact);


/**
 *  This will clean the start port and end port information.
 * */
extern void line_factory_unregister_all (line_factory_t *fact);

extern void line_factory_destory (line_factory_t *fact);

#endif
