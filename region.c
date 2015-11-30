#include "utils.h"
#include "region.h"
#include "component-protected.h"

#include <string.h>

struct _region_private {
    rectangle_t range;
};

/****************   class chain   *********************/

static void paint(component_t *co, canvas_t *ca) {
    region_t *re = co;

    xfunc_error_log("%lf %lf %lf %lf\n",
            re->priv->range.center.x,
            re->priv->range.center.y,
            re->priv->range.width,
            re->priv->range.height);


    cairo_save (ca->cr);

    cairo_set_source_rgb (ca->cr, 1.0, 1.0, 1.0);
    rectangle_paint (&re->priv->range, ca);

    cairo_set_source_rgba (ca->cr, 1.0, 1.0, 1.0, 0.1);

    cairo_fill (ca->cr);

    cairo_restore (ca->cr);

}


static void destroy (component_t *co) {
    region_t *re = co;

    xfree (re->priv);
}

static component_class inherent_class = {
    .paint   = paint,
    .destroy = destroy
};


/***************************************************/

static region_private *private_create (void) {
    region_private *priv = xcalloc (1, sizeof (region_private));

    return priv;
}


region_t *region_create (void) {
    region_t *re = xmalloc (sizeof (region_t));

    component_init_class (re, REGION_TYPE, &inherent_class);
    
    re->priv = private_create ();

    return re;
}


void region_set_range (region_t *re, rectangle_t *rect) {
    re->priv->range = *rect;
}

rectangle_t *region_get_range (region_t *re) {
    return &re->priv->range;
}
