#ifndef __UML_BASIC_TYPE_POINT_LIST_TYPE_H__
#define __UML_BASIC_TYPE_POINT_LIST_TYPE_H__


#include "point.h"
#include "../double_list-template.h"

GENERAL_DLIST_MODULE_DEF(point)

typedef DLIST_NODE(point) point_unit_t;
typedef DLIST(point) point_list_t;

#define point_unit_create DLIST_NODE_CREATE(point)
#define point_unit_destory DLIST_NODE_DESTROY(point)

#define point_list_create DLIST_CREATE(point)
#define point_list_destory DLIST_DESTROY(point)

#define for_each_point_unit_in_point_list(pu, pl)                           \
    for_each_node_in_double_list(pu, pl)


#define point_list_append_list DLIST_APPEND_LIST(point)
#define point_list_append_point_unit DLIST_APPEND_NODE(point)
#define point_list_append_point DLIST_APPEND_DATA(point)

#endif
