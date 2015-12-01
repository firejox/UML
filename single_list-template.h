#ifndef __UML_MEOW_SLIST_H__
#define __UML_MEOW_SLIST_H__

#define SLIST_NODE(TYPE) single_list_##TYPE##_node_t
#define SLIST_NODE_CREATE(TYPE) single_list_##TYPE##_node_create
#define SLIST_NODE_DESTROY(TYPE) single_list_##TYPE##_node_destroy

#define SLIST(TYPE) single_list_##TYPE##_t
#define SLIST_CREATE(TYPE) single_list_##TYPE##_create
#define SLIST_DESTROY(TYPE) single_list_##TYPE##_destroy

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
extern single_list_##TYPE##_node_t                                              \
                *single_list_##TYPE##_node_create(TYPE##_t *data);              \
extern void single_list_##TYPE##_node_destroy                                   \
                    (single_list_##TYPE##_node_t *nd);
                                                                                
#define GENERAL_SLIST_MODULE_LIST_DEF(TYPE)                                     \
typedef struct _single_list_##TYPE {                                            \
    single_list_##TYPE##_node_t *head;                                          \
} single_list_##TYPE##_t;                                                       \
extern single_list_##TYPE##_t *single_list_##TYPE##_create(void);               \
extern void single_list_##TYPE##_destroy(single_list_##TYPE##_t *li);

#define GENERAL_SLIST_MODULE_DEF(TYPE)                                          \
    GENERAL_SLIST_MODULE_NODE_DEF(TYPE)                                         \
    GENERAL_SLIST_MODULE_LIST_DEF(TYPE)

#define GENERAL_SLIST_MODULE_NODE_IMPL(TYPE, DESTROY_FUNC)                      \
single_list_##TYPE##_node_t                                                     \
                *single_list_##TYPE##_node_create(TYPE##_t *data)               \
{                                                                               \
    single_list_##TYPE##_node_t *tmp = xmalloc(sizeof(single_list_##TYPE##_t)); \
    tmp->data = data;                                                           \
    tmp->next = NULL;                                                           \
    return tmp;                                                                 \
}                                                                               \
void single_list_##TYPE##_node_destroy (single_list_##TYPE##_node_t *nd)        \
{                                                                               \
    if (nd) {                                                                   \
        nd->next = NULL;                                                        \
        DESTROY_FUNC(nd->data);                                                 \
        xfree(nd);                                                              \
    }                                                                           \
}                                                                               \

#define GENERAL_SLIST_MODULE_LIST_IMPL(TYPE)                                    \
single_list_##TYPE##_t                                                          \
                *single_list_##TYPE##_create(void)                              \
{                                                                               \
    single_list_##TYPE##_t *tmp = xmalloc(sizeof(single_list_##TYPE##_t));      \
    tmp->head = NULL;                                                           \
    return tmp;                                                                 \
}                                                                               \
void single_list_##TYPE##_destroy(single_list_##TYPE##_t *li)                   \
{                                                                               \
    single_list_##TYPE##_node_t *p, *q = NULL;                                  \
    if (li == NULL)                                                             \
        return;                                                                 \
    for_each_node_in_single_list(p, li) {                                       \
        if (q)                                                                  \
            single_list_##TYPE##_node_destroy(q);                               \
        else                                                                    \
            li->head = NULL;                                                    \
        q = p;                                                                  \
    }                                                                           \
    single_list_##TYPE##_node_destroy(q);                                       \
    xfree(li);                                                                  \
}

#define GENERAL_SLIST_MODULE_IMPL(TYPE, DESTROY_FUNC)                           \
    GENERAL_SLIST_MODULE_NODE_IMPL(TYPE, DESTROY_FUNC)                          \
    GENERAL_SLIST_MODULE_LIST_IMPL(TYPE)
#endif
