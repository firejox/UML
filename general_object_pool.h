#ifndef __UML_GENERAL_OBJECT_POOL_H__
#define __UML_GENERAL_OBJECT_POOL_H__

#include "single_list-template.h"
#include "general_object.h"

GENERAL_SLIST_MODULE_DEF(general_object)

typedef struct _general_object_pool {
    SLIST(general_object) list;
} general_object_pool_t;

extern general_object_pool_t *general_object_pool_create (void);

extern void general_object_pool_destory (general_object_pool_t*);

#endif
