#ifndef __UML_MEOW_COMMON_H__
#define __UML_MEOW_COMMON_H__


#ifndef NULL 
#define NULL ((void*)0)
#endif

#define PP_REVERSE \
    7, 6, 5, 4, 3, 2, 1, 0
#define PP_NARG_N(_1, _2, _3, _4, _5, _6, _7, N, ...) N

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

#define GENERAL_MODULE_6(TYPE, ...)                     \
    GENERAL_MODULE_MAKE_MODULE(TYPE)                    \
    GENERAL_MODULE_5(__VA_ARGS__)

#define GENERAL_MODULE_N(N, ...)                        \
    SPLICE(GENERAL_MODULE_,N)(__VA_ARGS__)

#define GENERAL_MODULE(...)                             \
    GENERAL_MODULE_BEFORE_MAKE()                        \
    GENERAL_MODULE_N(PP_NARGS(__VA_ARGS__), __VA_ARGS__)\
    GENERAL_MODULE_AFTER_MAKE()

#define GENERAL_MODULE_BEFORE_MAKE()
#define GENERAL_MODULE_MAKE_MODULE()
#define GENERAL_MODULE_AFTER_MAKE()

#endif
