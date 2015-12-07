#include "utils.h"
#include "line_decorate.h"
#include "object-protected.h"

/**
 * this part you should check the line struct
 *
 * */

struct _line_decorate_private {
    image_t *im;
    double angle;
};

/****************   class chain   *********************/

/***************  component class ********************/
static void paint (component_t *co, canvas_t *ca) {
    line_decorate_t *dec = co;
    const point_t *pt = NULL;
    double w, h;
    
    w = line_decorate_get_width  (dec);
    h = line_decorate_get_height (dec);

    pt = object_get_pos (dec);

    
    cairo_save (ca->cr);

    cairo_translate (ca->cr, pt->x, pt->y);

    cairo_rotate (ca->cr, dec->priv->angle);

    cairo_translate (ca->cr, - w/2, - h/2);

    image_paint (dec->priv->im, ca);
    
    cairo_restore (ca->cr);

}

static int is_inside (component_t *co, point_t *pt) { return 0; }

static int is_covered (component_t *co, rectangle_t *re) { return 0; }

static void destroy (component_t *co) {
    line_decorate_t *dec = co;

    image_unref (dec->priv->im);
    xfree (dec->priv);
}

/*************** object class *********************/

static void update (object_t *obj) {
    
}

static const rectangle_t *get_region (object_t *obj) { return NULL; }

static object_class inherent_class = 
{
    .p_class = {
        .paint      = paint,
        .is_inside  = is_inside,
        .is_covered = is_covered,
        .destroy    = destroy
    },
    .update = update,
    .get_region = get_region
};

/******************************************************/

static line_decorate_private *private_create (image_t *im) {
    line_decorate_private *priv = xmalloc (sizeof (line_decorate_private));

    priv->im = image_ref (im);
    priv->angle = 0.0;

    return priv;
}

line_decorate_t *line_decorate_create (image_t *im) {
    line_decorate_t *dec = xmalloc (sizeof (line_decorate_t));

    object_init_class (dec, LINE_DECORATE_TYPE, &inherent_class);
    dec->priv = private_create (im);

    return dec;
}

int line_decorate_get_width (line_decorate_t *dec) {
    return image_get_width (dec->priv->im);
}

int line_decorate_get_height (line_decorate_t *dec) {
    return image_get_height (dec->priv->im);
}

void line_decorate_set_angle (line_decorate_t *dec, double angle) {
    dec->priv->angle = angle;
}


