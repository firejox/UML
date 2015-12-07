
#include "line-protected.h"
#include "line_factory.h"
#include "utils.h"

struct _line_factory_private {
    port_object_t *st_port;
    port_object_t *ed_port;
    
    point_t       st_pos;
    point_t       ed_pos;
    
    line_t        sample;
    
    line_factory_class *_class;
};


static void line_setup_decorates_by_factory (
                        line_t *con, line_factory_t *fact) {
    image_t *im;

    if (fact->priv->_class->get_start_decorate_image) {
        im = fact->priv->_class->get_start_decorate_image();
        
        line_set_start_decorate (con, line_decorate_create (im));
    } 

    if (fact->priv->_class->get_end_decorate_image) {
        im = fact->priv->_class->get_end_decorate_image();

        line_set_end_decorate (con, line_decorate_create (im));
    
    }
}
    

static line_t *line_create_by_factory (line_factory_t *fact) {
    line_t *con = xcalloc (1, sizeof (line_t));

    line_init_class (con, fact->priv->_class);

    line_setup_decorates_by_factory (con, fact);

    return con;
}

/**
 * private_create - create line_factory_private for initial
 * @_class - the class method for the line_factory
 *
 * Note. Please make sure the methods in line_class and 
 *  line_factory class is already assigned.
 * */
static line_factory_private *private_create (line_factory_class *_class) {
    line_factory_private *priv = xcalloc (1, sizeof (line_factory_private));
    
    priv->_class = _class;

    return priv;
}


/**
 * line_factory_create - create line_factory with `_class` method
 * @_class - the line_factory method for build
 *
 * Note. 
 * */
line_factory_t *line_factory_create (line_factory_class *_class) {
    line_factory_t *fact = xmalloc (sizeof (line_factory_t));

    fact->priv = private_create (_class);
   
    line_init_class (&fact->priv->sample, _class);
    line_setup_decorates_by_factory (&fact->priv->sample, fact);
        
    return fact;
}


void line_factory_register_start_port (
                line_factory_t *fact, port_object_t *port) {
    fact->priv->st_port = port;

    port_object_get_absolute_pos (port, &fact->priv->st_pos);
    fact->priv->ed_pos = fact->priv->st_pos;
}

void line_factory_register_end_port (
                line_factory_t *fact, port_object_t *port) {
    if (fact->priv->st_port) {
        fact->priv->ed_port = port;
    }
}

void line_factory_setup_end_pos (line_factory_t *fact, point_t *pos) {
    if (fact->priv->st_port) {
        fact->priv->ed_pos = *pos;
    }
}

line_t *line_factory_get_sample (line_factory_t *fact) {
    line_path_t *path;
    line_decorate_t *st_dec, *ed_dec;

    if (fact->priv->st_port) {
        path = ((line_class*)fact->priv->_class)->path_create 
                        (&fact->priv->st_pos, &fact->priv->ed_pos);

        line_set_line_path (&fact->priv->sample, path);

        st_dec = line_get_start_decorate (&fact->priv->sample);
        if (st_dec)
            ((line_class*)fact->priv->_class)->start_decorate_update 
                        (st_dec, path);

        ed_dec = line_get_end_decorate (&fact->priv->sample);
        if (ed_dec)
            ((line_class*)fact->priv->_class)->end_decorate_update
                        (ed_dec, path);

        return &fact->priv->sample;
    }

    return NULL;
}

void line_factory_unregister_all (line_factory_t *fact) {
    fact->priv->st_port = NULL;
    fact->priv->ed_port = NULL;
}

void line_factory_produce_one (line_factory_t *fact) {
    basic_object_t *st_obj, *ed_obj;
    line_t *con;

    st_obj = port_object_get_basic_object (fact->priv->st_port);
    ed_obj = port_object_get_basic_object (fact->priv->ed_port);

    if (st_obj != ed_obj) { 
        con = line_create_by_factory (fact);
        line_set_start_port (con, fact->priv->st_port);
        line_set_end_port (con, fact->priv->ed_port);

        port_object_link_line (fact->priv->st_port, con);
        port_object_link_line (fact->priv->ed_port, con);

        line_update (con);
    }

}


void line_factory_destory (line_factory_t *fact) {
    line_t *con = &fact->priv->sample;

    line_set_line_path (con, NULL);
    line_set_start_decorate (con, NULL);
    line_set_end_decorate (con, NULL);
    
    xfree (fact->priv);
    xfree (fact);
}
