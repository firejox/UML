#ifndef __UML_GENERAL_OBJECT_POOL_H__
#define __UML_GENERAL_OBJECT_POOL_H__

#include "double_list-template.h"
#include "general_object-type.h"

GENERAL_DLIST_MODULE_DEF(general_object)

typedef DLIST_NODE(general_object) general_object_unit_t;
typedef DLIST(general_object) general_object_pool_t;

#define general_object_pool_create DLIST_CREATE(general_object)
#define general_object_pool_destroy DLIST_DESTROY(general_object)

#define general_object_unit_create DLIST_NODE_CREATE(general_object)
#define general_object_unit_destroy DLIST_NODE_DESTROY(general_object)

#define GO_UNIT_GET_COMPONENT(p) GO_GET_COMPONENT((p)->data)
#define GO_UNIT_GET_TYPE(p) GO_GET_TYPE((p)->data)

#include "general_object.h"

#endif
