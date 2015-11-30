#ifndef __UML_MEOW_DLIST_H__
#define __UML_MEOW_DLIST_H__


#define DLIST_NODE(TYPE) double_list_##TYPE##_node_t
#define DLIST_NODE_CREATE(TYPE) double_list_##TYPE##_node_create
#define DLIST_NODE_DESTROY(TYPE) double_list_##TYPE##_node_destroy

#define DLIST(TYPE) double_list_##TYPE##_t
#define DLIST_CREATE(TYPE) double_list_##TYPE##_create
#define DLIST_DESTROY(TYPE) double_list_##TYPE##_destroy

#define for_each_node_in_double_list(p, list)                                   \
    for (p = (list) ? (list)->head : NULL; p; p = p->next)

#define for_each_node_in_double_list_reverse(p, list)                           \
    for (p = (list) ? (list)->tail : NULL; p; p = p->prev)

#define double_list_prepend(nd, list)                                           \
    do {                                                                        \
        if ((list)->head) {                                                     \
            (list)->head->prev = nd;                                            \
            nd->next = (list)->head;                                            \
            (list)->head = nd;                                                  \
        } else {                                                                \
            (list)->head = (list)->tail = nd;                                   \
        }                                                                       \
    } while (0)

#define double_list_append(nd, list)                                            \
    do {                                                                        \
        if ((list)->tail) {                                                     \
            (list)->tail->next = nd;                                            \
            nd->prev = (list)->tail;                                            \
            (list)->tail = nd;                                                  \
        } else {                                                                \
            (list)->head = (list)->tail = nd;                                   \
        }                                                                       \
    } while (0)

#define GENERAL_DLIST_MODULE_NODE_DEF(TYPE)                                     \
typedef struct _double_list_##TYPE##_node {                                     \
    TYPE##_t *data;                                                             \
    struct _double_list_##TYPE##_node *next;                                    \
    struct _double_list_##TYPE##_node *prev;                                    \
} double_list_##TYPE##_node_t;                                                  \
extern double_list_##TYPE##_node_t                                              \
        *double_list_##TYPE##_node_create(TYPE##_t *data);                      \
extern void double_list_##TYPE##_node_destroy                                   \
                                    (double_list_##TYPE##_node_t *nd);

#define GENERAL_DLIST_MODULE_LIST_DEF(TYPE)                                     \
typedef struct _double_list_##TYPE {                                            \
    double_list_##TYPE##_node_t *head;                                          \
    double_list_##TYPE##_node_t *tail;                                          \
} double_list_##TYPE##_t;                                                       \
extern double_list_##TYPE##_t *double_list_##TYPE##_create(void);               \
extern void double_list_##TYPE##_destroy(double_list_##TYPE##_t *li);


#define GENERAL_DLIST_MODULE_DEF(TYPE) \
    GENERAL_DLIST_MODULE_NODE_DEF(TYPE)\
    GENERAL_DLIST_MODULE_LIST_DEF(TYPE)

#define GENERAL_DLIST_MODULE_NODE_IMPL(TYPE, DESTROY_FUNC)                      \
double_list_##TYPE##_node_t                                                     \
        *double_list_##TYPE##_node_create(TYPE##_t *data) {                     \
    double_list_##TYPE##_node_t *nd = xmalloc(                                  \
                                sizeof(double_list_##TYPE##_node_t));           \
    nd->data = data;                                                            \
    nd->prev = nd->next = NULL;                                                 \
    return nd;                                                                  \
}                                                                               \
void double_list_##TYPE##_node_destroy(double_list_##TYPE##_node_t *nd) {       \
    nd->prev = nd->next = NULL;                                                 \
    DESTROY_FUNC(nd->data);                                                     \
    xfree(nd);                                                                  \
}

#define GENERAL_DLIST_MODULE_LIST_IMPL(TYPE)                                    \
double_list_##TYPE##_t *double_list_##TYPE##_create(void) {                     \
    double_list_##TYPE##_t *tmp = xmalloc (sizeof (double_list_##TYPE##_t));    \
    tmp->head = tmp->tail = NULL;                                               \
    return tmp;                                                                 \
}                                                                               \
void double_list_##TYPE##_destroy (double_list_##TYPE##_t *li) {                \
    double_list_##TYPE##_node_t *p, *q = NULL;                                  \
    for_each_node_in_double_list(p, li) {                                       \
        if (q)                                                                  \
            double_list_##TYPE##_node_destroy(q);                               \
        else                                                                    \
            li->head = li->tail = NULL;                                         \
        q = p;                                                                  \
    }                                                                           \
    if (q)                                                                      \
        double_list_##TYPE##_node_destroy(q);                                   \
    xfree (li);                                                                 \
}


#define GENERAL_DLIST_MODULE_IMPL(TYPE, DESTROY_FUNC)                           \
    GENERAL_DLIST_MODULE_NODE_IMPL(TYPE, DESTROY_FUNC)                          \
    GENERAL_DLIST_MODULE_LIST_IMPL(TYPE)


#endif
