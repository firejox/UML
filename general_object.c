#include "general_object.h"
#include "utils.h"


/*
 * general constructor and destructor generation
 * */

#define GENERAL_MODULE_BEFORE_MAKE()

#define GENERAL_MODULE_MAKE_MODULE(TYPE)                            \
general_object_t *general_object_create_from_##TYPE          \
                        (TYPE##_t *_obj) {                          \
    general_object_t *tmp = xmalloc (sizeof (general_object_t));    \
    tmp->obj.__##TYPE##_obj = _obj;                                 \
    tmp->type = GO_##TYPE##_type;                                   \
    return tmp;                                                     \
}

#define GENERAL_MODULE_AFTER_MAKE()                                 \
general_object_destroy (general_object_t *_obj) {            \
    component_destroy(_obj->obj.__component_obj);                   \
    xfree (_obj);                                                   \
}

GENERAL_MODULE(GENRAL_OBJECT_TYPE_LIST)
