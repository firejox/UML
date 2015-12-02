#ifndef __UML_GENERAL_OBJECT_H__
#define __UML_GENERAL_OBJECT_H__


#include "common.h"


#include "general_object-type.h"

#include "composite_object.h"
#include "basic_object.h"


#define GO_GET_COMPONENT(go_p) ((go_p)->obj.__component_obj)
#define GO_GET_TYPE(go_p) ((go_p)->type)
#define GO_CREATE(TYPE) general_object_create_from_##TYPE
#define GO_TYPE(TYPE) GO_##TYPE##_type

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
        union {                                                     

#define GENERAL_MODULE_MAKE_MODULE(TYPE)                            \
            TYPE##_t *__##TYPE##_obj;                               

#define GENERAL_MODULE_AFTER_MAKE()                                 \
            component_t *__component_obj;                           \
        } obj;                                                      \
        general_object_type type;                                   \
    };

GENERAL_MODULE(GENRAL_OBJECT_TYPE_LIST)


/*
 * general constructor and destructor generation
 * */

#define GENERAL_MODULE_BEFORE_MAKE()

#define GENERAL_MODULE_MAKE_MODULE(TYPE)                            \
extern general_object_t *general_object_create_from_##TYPE   \
                        (TYPE##_t *_obj) ;
#define GENERAL_MODULE_AFTER_MAKE()                                 \
extern void general_object_destroy (general_object_t *_obj);


GENERAL_MODULE(GENRAL_OBJECT_TYPE_LIST)


#define GENERAL_MODULE_BEFORE_MAKE()
#define GENERAL_MODULE_MAKE_MODULE()
#define GENERAL_MODULE_AFTER_MAKE()

#endif
