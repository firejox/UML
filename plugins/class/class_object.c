#include "../../utils.h"
#include "../../basic_object-protected.h"
#include "class_object.h"
#include <pango/pangocairo.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define FONT "Sans Bold 16"
#define PADDING_H 10
#define PADDING_W 20

static int class_object_count = 1;
static char default_name[20];

struct _class_object_private {
    rectangle_t range;
    rectangle_t c_name;
    rectangle_t attrs;
    rectangle_t methods;
};

static void update_size (class_object_t *obj) {
    int w, h;
    double width, height;

    GdkScreen    *scr = gdk_screen_get_default();
    PangoContext *context;
    PangoLayout *layout;
    PangoFontDescription *desc;
    const char *name;

    name = basic_object_get_name (obj);

    {
        context = gdk_pango_context_get_for_screen (scr);

        layout = pango_layout_new (context);

        pango_layout_set_text (layout, name, -1);

        desc = pango_font_description_from_string (FONT);

        pango_layout_set_font_description (layout, desc);

        pango_font_description_free (desc); 
    }

    pango_layout_get_size (layout, &w, &h);
    
    width = ((double)w / PANGO_SCALE) + PADDING_W * 2;

    height = ((double)h / PANGO_SCALE) + PADDING_H * 2;

    { 
        obj->priv->range.width = width;
        obj->priv->range.height = height * 3;

        obj->priv->c_name.center.y = -height;
        obj->priv->c_name.width = width;
        obj->priv->c_name.height = height;

        obj->priv->attrs.width = width;
        obj->priv->attrs.height = height;

        obj->priv->methods.center.y = height;
        obj->priv->methods.width = width;
        obj->priv->methods.height = height;
    }
    
    g_object_unref (layout);
    g_object_unref (context);
}

static void port_pos_update (class_object_t *obj) {
    SLIST(port_object) *li;
    SLIST_NODE(port_object) *p;
    const point_t *pt;
    point_t tmp;

    li = basic_object_get_ports (obj);
    
    for_each_node_in_single_list (p, li) {
        pt = object_get_pos (p->data);

        tmp.y = pt->y;

        if (double_equal(pt->x, 0.0)) {
            tmp.x = pt->x;
            if (pt->y > 0.0)
                tmp.y =    obj->priv->range.height / 2;
            else 
                tmp.y =  - obj->priv->range.height / 2;
        } else {
            tmp.y = pt->y;
            if (pt->x > 0.0)
                tmp.x =   obj->priv->range.width / 2;
            else
                tmp.x = - obj->priv->range.width / 2;
        }

        object_set_pos (p->data, &tmp);
    }
}

static PangoLayout *get_font_layout (const char *str, cairo_t *cr) {
    PangoLayout *layout;
    PangoFontDescription *desc;

    layout = pango_cairo_create_layout (cr);

    pango_layout_set_text (layout, str, -1);

    desc = pango_font_description_from_string (FONT);

    pango_layout_set_font_description (layout, desc);

    pango_font_description_free (desc);   


    return layout;
}

static void draw_text (PangoLayout *layout, point_t *cen_pos, canvas_t *ca) {
    int width, height;


    cairo_save (ca->cr);
        
    cairo_translate (ca->cr, cen_pos->x, cen_pos->y);

    pango_cairo_update_layout (ca->cr, layout);

    pango_layout_get_size (layout, &width, &height);

    cairo_translate (ca->cr, -((double)width / PANGO_SCALE) / 2,
                            -((double)height / PANGO_SCALE) / 2);

    pango_cairo_show_layout (ca->cr, layout);

    cairo_restore (ca->cr);

    g_object_unref (layout);

}

static void paint_part (rectangle_t *part, canvas_t *ca) {
    double gray = (double)0xb3 / 0xff;
    cairo_save (ca->cr);

    {
        cairo_set_line_width (ca->cr, 9);

        cairo_set_source_rgb (ca->cr, 0.0, 0.0, 0.0);

        rectangle_paint (part, ca);

        cairo_set_source_rgb (ca->cr, gray, gray, gray);

        cairo_fill (ca->cr);
    }

    cairo_restore (ca->cr);
}

/****************   class chain   *********************/

/***************  component class ********************/
static void paint (component_t *co, canvas_t *ca) {
    class_object_t *obj = co;
    PangoLayout *layout = NULL;
    const char *c_name;

    cairo_save (ca->cr);

    {   
        cairo_translate (ca->cr,
                obj->priv->range.center.x,
                obj->priv->range.center.y);
        
        {
            paint_part (&obj->priv->c_name, ca);
        
            c_name = basic_object_get_name (obj);

            layout = get_font_layout (c_name, ca->cr);

            draw_text (layout, &obj->priv->c_name.center, ca);
        }

        {
            paint_part (&obj->priv->attrs, ca);

            layout = get_font_layout ("", ca->cr);

            draw_text (layout, &obj->priv->attrs.center, ca);
        }

        {
            paint_part (&obj->priv->methods, ca);

            layout = get_font_layout ("", ca->cr);

            draw_text (layout, &obj->priv->methods.center, ca);   
        }

    }
    
    cairo_restore (ca->cr);
}

static int is_inside (component_t *co, point_t *pt) { 
    class_object_t *obj = co;

    return is_rectangle_inside (&obj->priv->range, pt); 
}

static int is_covered (component_t *co, rectangle_t *re) {
    class_object_t *obj = co;

    return is_rectangle_covered (&obj->priv->range, re); 
}

static void destroy (component_t *co) {
    class_object_t *obj = co;

    xfree (obj->priv);
}

/*************   object class   *******************/

static void update (object_t *obj) {
    class_object_t *c_obj = obj;
    double width, height;
    const point_t *pt;
    

    width = c_obj->priv->range.width;
    height = c_obj->priv->range.height;

    update_size (c_obj);
    
    if (!double_equal (width, c_obj->priv->range.width) 
            || !double_equal (height, c_obj->priv->range.height)) 
        port_pos_update (c_obj);
    
    pt = object_get_pos (c_obj);

    if (!is_same_point (&c_obj->priv->range.center, pt)) 
        c_obj->priv->range.center = *pt; 
    
}

static const rectangle_t *get_region (object_t *obj) {
    class_object_t *c_obj = obj;

    return &c_obj->priv->range;
}

/*******************  basic_object ****************/

static port_object_t *get_port_object (basic_object_t *obj,
                                                     point_t *pos) {
    class_object_t *c_obj = obj; 
    const point_t *pt;

    double angle = atan2(c_obj->priv->range.height, c_obj->priv->range.width);
    double a_arr[] = {-M_PI + angle, -angle, angle, M_PI - angle};


    SLIST_NODE(port_object) *p;
    SLIST(port_object) *li = basic_object_get_ports (obj);

    int i, pos_at;

    if (is_inside (c_obj, pos)) {
        pt = object_get_pos (c_obj);

        angle = atan2 (pos->y - pt->y, pos->x - pt->x);

        for (i = 0; i < 3; i++)
            if (islessequal (a_arr[i], angle) &&
                isless (angle, a_arr[i+1]))
            break;
        pos_at = i;

        for_each_node_in_single_list (p, li) {
            pt = object_get_pos (p->data);
            angle  = atan2 (pt->y, pt->x);

            for (i = 0; i < 3; i++)
                if (islessequal (a_arr[i], angle) &&
                        isless (angle, a_arr[i+1]))
                    break;

            if (pos_at == i)
                return p->data;

        }
   
    }

    return NULL;
}

static basic_object_class inherent_class = 
{
    .p_class = {
        .p_class = {
            .paint      = paint,
            .is_inside  = is_inside,
            .is_covered = is_covered,
            .destroy    = destroy
        },
        .update = update,
        .get_region = get_region
    },
    .get_port_object = get_port_object
};


/***************************************************/



static class_object_private *private_create (void) {
    class_object_private *priv = xcalloc (1, sizeof (class_object_private));

    return priv;
}


class_object_t *class_object_create (point_t *pt) {
    class_object_t *obj = xmalloc (sizeof (class_object_t));
    port_object_t *port;

    point_t pos[4] = {{1.0, 0.0} , {0.0, 1.0}, {-1.0, 0.0}, {0.0, -1.0}};
    int i;

    basic_object_init_class (obj, &inherent_class);
    obj->priv = private_create ();


    snprintf (default_name, sizeof (default_name),
                         "Class %d", class_object_count++);

    basic_object_set_name (obj, default_name);
    
    object_set_pos (obj, pt);

    for (int i = 0; i < 4; i++) {
        port = port_object_create (obj, &pos[i]);
        basic_object_add_port (obj, port);
    }
    
    object_update (obj);

    return obj;
}
