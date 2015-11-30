#ifndef __UML_COMPOSITE_OBJECT_H__
#define __UML_COMPOSITE_OBJECT_H__

typedef struct _composite_object composite_object_t;
typedef struct _composite_object_private composite_object_private;

#include "object.h"
#include "general_object_pool.h"



struct _composite_object {
    object_t parent;
    composite_object_private *priv;
};

extern composite_object_t *composite_object_group(general_object_pool_t *gop);


extern general_object_pool_t *composite_object_ungroup(composite_object_t *co);


#endif
