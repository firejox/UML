#ifndef __UML_MEOW_COMMON_H__
#define __UML_MEOW_COMMON_H__


#ifndef NULL 
#define NULL ((void*)0)
#endif

#define PP_REVERSE \
    5, 4, 3, 2, 1, 0
#define PP_NARG_N(_1, _2, _3, _4, _5, N, ...) N

#define PP_NARGS_(...) PP_NARG_N(__VA_ARGS__)

#define PP_NARGS(...) \
    PP_NARGS_(__VA_ARGS__, PP_REVERSE)


#define SPLICE(a,b) SPLICE_1(a,b)
#define SPLICE_1(a,b) SPLICE_0(a,b)
#define SPLICE_0(a,b) a##b

#define GENERAL_MODULE_1(TYPE)                          \
    GENERAL_MODULE_MAKE_MODULE(TYPE)

#define GENERAL_MODULE_2(TYPE, ...)                     \
    GENERAL_MODULE_MAKE_MODULE(TYPE)                    \
    GENERAL_MODULE_1(__VA_ARGS__)                       \

#define GENERAL_MODULE_3(TYPE, ...)                     \
    GENERAL_MODULE_MAKE_MODULE(TYPE)                    \
    GENERAL_MODULE_2(__VA_ARGS__)

#define GENERAL_MODULE_4(TYPE, ...)                     \
    GENERAL_MODULE_MAKE_MODULE(TYPE)                    \
    GENERAL_MODULE_3(__VA_ARGS__)

#define GENERAL_MODULE_5(TYPE, ...)                     \
    GENERAL_MODULE_MAKE_MODULE(TYPE)                    \
    GENERAL_MODULE_4(__VA_ARGS__)

#define GENERAL_MODULE_N(N, ...)                        \
    SPLICE(GENERAL_MODULE_,N)(__VA_ARGS__)

#define GENERAL_MODULE(...)                             \
    GENERAL_MODULE_BEFORE_MAKE()                        \
    GENERAL_MODULE_N(PP_NARGS(__VA_ARGS__), __VA_ARGS__)\
    GENERAL_MODULE_AFTER_MAKE()

#define GENERAL_MODULE_BEFORE_MAKE()
#define GENERAL_MODULE_MAKE_MODULE()
#define GENERAL_MODULE_AFTER_MAKE()

#if 0
/*
 * may not need to  use yet
 *
 * */

#define GENERAL_DLIST_MODULE_NODE_DEF(TYPE)                                     \
typedef struct _double_list_##TYPE##_node {                                     \
    TYPE##_t *data;                                                             \
    struct _double_list_##TYPE##_node_t *next;                                  \
    struct _double_list_##TYPE##_node_t *prev;                                  \
} double_list_##TYPE##_node_t;                                                  \
inline double_list_##TYPE##_node_t                                              \
        *double_list_##TYPE##_node_create(TYPE##_t *data);                      \
inline void double_list_##TYPE##_node_destory(double_list_##TYPE##_node_t *nd);

#define GENERAL_DLIST_MODULE_LIST_DEF(TYPE)                                     \
typedef struct _double_list_##TYPE {                                            \
    double_list_##TYPE##_node_t *head;                                          \
    double_list_##TYPE##_node_t *tail;                                          \
} double_list_##TYPE##_t;                                                       \
inline double_list_##TYPE##_t *double_list_##TYPE##_create(void);               \
inline void double_list_##TYPE##_destory(double_list_##TYPE##_t *li);


inline void double_list_##TYPE##_node_destory(double_list_##TYPE##_node_t *nd) {
    DESTORY_FUNC(nd->data);
    xfree(nd);
}

#endif
#endif
