#ifndef __UML_REGION_H__
#define __UML_REGION_H__


#include "component.h"

typedef struct _region region_t;
typedef struct _region_class region_class;
typedef struct _region_private region_private;

struct _region {
    component_t parent;
    region_private *priv;
};

struct _region_class {
    component_class p_class;
};


extern region_t *region_create(void);
extern void region_set_range(region_t *re, rectangle_t *rect);
extern rectangle_t *region_get_range(region_t *re);


#endif
