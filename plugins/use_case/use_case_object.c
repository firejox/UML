#include "../../utils.h"
#include "../../basic_object-protected.h"
#include "use_case_object.h"
#include <pango/pangocairo.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define FONT "Sans Bold 16"
#define PADDING_H 20
#define PADDING_W 30

static int use_case_object_count = 1;
static char default_name[25];

struct _use_case_object_private {
    rectangle_t region;
    ellipse_t   range;
};


static void update_size (use_case_object_t *obj) {
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

    height = ((double)h / PANGO_SCALE) + PADDING_H * 2 ;

    { 
        obj->priv->region.width = width;
        obj->priv->region.height = height;

        obj->priv->range.radius = width / 2;
        obj->priv->range.rate = height / width;
    }

    g_object_unref (layout);
    g_object_unref (context);
}

static void port_pos_update (use_case_object_t *obj) {
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
                tmp.y =    obj->priv->region.height / 2;
            else 
                tmp.y =  - obj->priv->region.height / 2;
        } else {
            tmp.y = pt->y;
            if (pt->x > 0.0)
                tmp.x =   obj->priv->region.width / 2;
            else
                tmp.x = - obj->priv->region.width / 2;
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

static void paint_part (ellipse_t *part, canvas_t *ca) {
    double gray = (double)0xb3 / 0xff;
    cairo_save (ca->cr);

    {
        cairo_set_line_width (ca->cr, 9);

        cairo_set_source_rgb (ca->cr, 0.0, 0.0, 0.0);

        ellipse_paint (part, ca);

        cairo_set_source_rgb (ca->cr, gray, gray, gray);

        cairo_fill (ca->cr);
    }

    cairo_restore (ca->cr);
}

/****************   class chain   *********************/

/***************  component class ********************/
static void paint (component_t *co, canvas_t *ca) {
    use_case_object_t *obj = co;
    PangoLayout *layout = NULL;
    const char *u_name;

    cairo_save (ca->cr);

    {  
       /* 
        cairo_translate (ca->cr,
                obj->priv->range.center.x,
                obj->priv->range.center.y);
        */
        {
            paint_part (&obj->priv->range, ca);
        
            u_name = basic_object_get_name (obj);

            layout = get_font_layout (u_name, ca->cr);

            draw_text (layout, &obj->priv->range.center, ca);
        }

    }
    
    cairo_restore (ca->cr);
}

static int is_inside (component_t *co, point_t *pt) { 
    use_case_object_t *obj = co;

    return is_ellipse_inside (&obj->priv->range, pt); 
}

static int is_covered (component_t *co, rectangle_t *re) {
    use_case_object_t *obj = co;

    return is_ellipse_covered (&obj->priv->range, re); 
}

static void destroy (component_t *co) {
    use_case_object_t *obj = co;

    xfree (obj->priv);
}

/*************   object class   *******************/

static void update (object_t *obj) {
    use_case_object_t *u_obj = obj;
    double width, height;
    const point_t *pt;


    width = u_obj->priv->region.width;
    height = u_obj->priv->region.height;

    update_size (u_obj);

    if (!double_equal (width, u_obj->priv->region.width) 
            || !double_equal (height, u_obj->priv->region.height)) 
        port_pos_update (u_obj);
    
    pt = object_get_pos (u_obj);

    if (!is_same_point (&u_obj->priv->range.center, pt)) {
        u_obj->priv->range.center = *pt; 
        u_obj->priv->region.center = *pt; 
    }

}

static const rectangle_t *get_region (object_t *obj) {
    use_case_object_t *u_obj = obj;

    return &u_obj->priv->region;
}

/*******************  basic_object ****************/

static port_object_t *get_port_object (basic_object_t *obj,
                                                     point_t *pos) {
    use_case_object_t *u_obj = obj; 
    const point_t *pt;

    double angle = atan2(u_obj->priv->region.height, u_obj->priv->region.width);
    double a_arr[] = {-M_PI + angle, -angle, angle, M_PI - angle};


    SLIST_NODE(port_object) *p;
    SLIST(port_object) *li = basic_object_get_ports (obj);

    int i, pos_at;

    if (is_inside (u_obj, pos)) {
        pt = object_get_pos (u_obj);

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

static use_case_object_private *private_create (void) {
    use_case_object_private *priv = NULL;
    priv = xcalloc (1, sizeof (use_case_object_private));    
    
    return priv;
}


use_case_object_t *use_case_object_create (point_t *pt) {
    use_case_object_t *obj = xmalloc (sizeof (use_case_object_t));

    port_object_t *port;

    point_t pos[4] = {{1.0, 0.0} , {0.0, 1.0}, {-1.0, 0.0}, {0.0, -1.0}};
    int i;

    basic_object_init_class (obj, &inherent_class);
    obj->priv = private_create ();


    snprintf (default_name, sizeof (default_name),
                         "use case %d", use_case_object_count++);

    basic_object_set_name (obj, default_name);
    
    object_set_pos (obj, pt);

    for (int i = 0; i < 4; i++) {
        port = port_object_create (obj, &pos[i]);
        basic_object_add_port (obj, port);
    }
    
    object_update (obj);

    return obj;

}
