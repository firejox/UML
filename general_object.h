#ifndef __UML_GENERAL_OBJECT_H__
#define __UML_GENERAL_OBJECT_H__


#include "utils.h"
#include "common.h"

#include "composite_object.h"
#include "class_object.h"
#include "use_case_object.h"

typedef enum _general_object_type general_object_type;

typedef struct _general_object general_object_t;


#define GENRAL_OBJECT_TYPE_LIST                                     \
    class_object, use_case_object, composite_object


/*
 *check exist empty argument
 * **/
#define GENERAL_MODULE_BEFORE_MAKE()
#define GENERAL_MODULE_AFTER_MAKE()
#define GENERAL_MODULE_MAKE_MODULE(TYPE)                            \
    typedef struct GENERAL_OBJECT_TYPE_IS_NOT_EMPTY general_object_t##TYPE;

GENERAL_MODULE(GENRAL_OBJECT_TYPE_LIST)


/*
 * enum detail generation
 * */
#define GENERAL_MODULE_BEFORE_MAKE()                                \
    enum _general_object_type {

#define GENERAL_MODULE_MAKE_MODULE(TYPE)                            \
        GO_##TYPE##_type,

#define GENERAL_MODULE_AFTER_MAKE()                                 \
        GO_INVALID_type                                             \
    };

GENERAL_MODULE(GENRAL_OBJECT_TYPE_LIST)

/*
 * general_object generation
 * */
#define GENERAL_MODULE_BEFORE_MAKE()                                \
    struct _general_object {                                        \
        general_object_type type;                                   \
        union {                                                     

#define GENERAL_MODULE_MAKE_MODULE(TYPE)                            \
            TYPE##_t *__##TYPE##_obj;                               

#define GENERAL_MODULE_AFTER_MAKE()                                 \
            component_t *__component_obj;                           \
        } obj;                                                      \
    };

GENERAL_MODULE(GENRAL_OBJECT_TYPE_LIST)


/*
 * general constructor and destructor generation
 * */

#define GENERAL_MODULE_BEFORE_MAKE()

#define GENERAL_MODULE_MAKE_MODULE(TYPE)                            \
static inline general_object_t *general_object_create_from_##TYPE   \
                        (TYPE##_t *_obj) {                          \
    general_object_t *tmp = xmalloc (sizeof (general_object_t));    \
    tmp->obj.__##TYPE##_obj = _obj;                                 \
    tmp->type = GO_##TYPE##_type;                                   \
    return tmp;                                                     \
}

#define GENERAL_MODULE_AFTER_MAKE()                                 \
static inline general_object_destory (general_object_t *_obj) {     \
    component_destory(_obj->obj.__component_obj);                   \
    xfree (_obj);                                                   \
}

GENERAL_MODULE(GENRAL_OBJECT_TYPE_LIST)


#undef GENRAL_OBJECT_TYPE_LIST
#define GENERAL_MODULE_BEFORE_MAKE()
#define GENERAL_MODULE_MAKE_MODULE()
#define GENERAL_MODULE_AFTER_MAKE()

#endif
