#ifndef __UML_MEOW_SLIST_H__
#define __UML_MEOW_SLIST_H__

#define SLIST_NODE(TYPE) single_list_##TYPE##_node_t
#define SLIST_NODE_CREATE(TYPE) single_list_##TYPE##_node_create
#define SLIST_NODE_DESTORY(TYPE) single_list_##TYPE##_node_destory

#define SLIST(TYPE) single_list_##TYPE##_t
#define SLIST_CREATE(TYPE) single_list_##TYPE##_create
#define SLIST_DESTORY(TYPE) single_list_##TYPE##_destory

#define for_each_node_in_single_list(p, list)                                   \
    for (p = (list) ? (list)->head : NULL; p; p = p->next)

#define for_each_node_in_single_list_with_data(p, data, list)                   \
    for (p = (list) ? (list)->head : NULL,                                      \
            data = (p == NULL) ? NULL:p->data;                                  \
            p != NULL;                                                          \
            ((p->next == NULL) ? (p = NULL):(p = p->next, data = p->data)))

#define single_list_prepend(list, node)                                         \
    do {                                                                        \
        if (!list) break;                                                       \
        node->next = (list)->head;                                              \
        (list)->head = node;                                                    \
    } while (0)

#define GENERAL_SLIST_MODULE_NODE_DEF(TYPE)                                     \
typedef struct _single_list_##TYPE##_node {                                     \
    TYPE##_t *data;                                                             \
    struct _single_list_##TYPE##_node *next;                                    \
} single_list_##TYPE##_node_t;                                                  \
extern inline single_list_##TYPE##_node_t                                       \
                *single_list_##TYPE##_node_create(TYPE##_t *data);              \
extern inline void single_list_##TYPE##_node_destory                            \
                    (single_list_##TYPE##_node_t *nd);
                                                                                
#define GENERAL_SLIST_MODULE_LIST_DEF(TYPE)                                     \
typedef struct _single_list_##TYPE {                                            \
    single_list_##TYPE##_node_t *head;                                          \
} single_list_##TYPE##_t;                                                       \
extern inline single_list_##TYPE##_t *single_list_##TYPE##_create(void);        \
extern inline void single_list_##TYPE##_destory(single_list_##TYPE##_t *li);

#define GENERAL_SLIST_MODULE_DEF(TYPE)                                          \
    GENERAL_SLIST_MODULE_NODE_DEF(TYPE)                                         \
    GENERAL_SLIST_MODULE_LIST_DEF(TYPE)

#define GENERAL_SLIST_MODULE_NODE_IMPL(TYPE, DESTORY_FUNC)                      \
inline single_list_##TYPE##_node_t                                              \
                *single_list_##TYPE##_node_create(TYPE##_t *data)               \
{                                                                               \
    single_list_##TYPE##_node_t *tmp = xmalloc(sizeof(single_list_##TYPE##_t)); \
    tmp->data = data;                                                           \
    tmp->next = NULL;                                                           \
    return tmp;                                                                 \
}                                                                               \
inline void single_list_##TYPE##_node_destory (single_list_##TYPE##_node_t *nd) \
{                                                                               \
    if (nd) {                                                                   \
        DESTORY_FUNC(nd->data);                                                 \
        xfree(nd);                                                              \
    }                                                                           \
}                                                                               \

#define GENERAL_SLIST_MODULE_LIST_IMPL(TYPE)                                    \
inline single_list_##TYPE##_t                                                   \
                *single_list_##TYPE##_create(void)                              \
{                                                                               \
    single_list_##TYPE##_t *tmp = xmalloc(sizeof(single_list_##TYPE##_t));      \
    tmp->head = NULL;                                                           \
    return tmp;                                                                 \
}                                                                               \
inline void single_list_##TYPE##_destory(single_list_##TYPE##_t *li)            \
{                                                                               \
    single_list_##TYPE##_node_t *p, *q = NULL;                                  \
    if (li == NULL)                                                             \
        return;                                                                 \
    for_each_node_in_single_list(p, li) {                                       \
        single_list_##TYPE##_node_destory(q);                                   \
        q = p;                                                                  \
    }                                                                           \
    single_list_##TYPE##_node_destory(q);                                       \
    xfree(li);                                                                  \
}

#define GENERAL_SLIST_MODULE_IMPL(TYPE, DESTORY_FUNC)                           \
    GENERAL_SLIST_MODULE_NODE_IMPL(TYPE, DESTORY_FUNC)                          \
    GENERAL_SLIST_MODULE_LIST_IMPL(TYPE)
#endif
