#ifndef __UML_GENERAL_OBJECT_POOL_H__
#define __UML_GENERAL_OBJECT_POOL_H__

#include "double_list-template.h"
#include "general_object-type.h"

GENERAL_DLIST_MODULE_DEF(general_object)

typedef DLIST_NODE(general_object) general_object_unit_t;
typedef DLIST(general_object) general_object_pool_t;

#define general_object_pool_create() DLIST_CREATE(general_object)()
#define general_object_pool_destroy(gop) DLIST_DESTROY(general_object)(gop)

#define general_object_unit_create(go) DLIST_NODE_CREATE(general_object)(go)
#define general_object_unit_destroy(gou) DLIST_NODE_DESTROY(general_object)(gou)

#define GO_UNIT_GET_COMPONENT(p) GO_GET_COMPONENT((p)->data)
#define GO_UNIT_GET_TYPE(p) GO_GET_TYPE((p)->data)

#include "general_object.h"

#endif
