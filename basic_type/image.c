#include "../utils.h"
#include "image.h"
#include <gdk/gdk.h>

image_t *image_create_from_file (const char *fn, int width, int height) {
    GdkPixbuf *pb = NULL;
    image_t *im = NULL;
    cairo_t *cr;

    int w, h;
    unsigned char *data = NULL;

    pb = gdk_pixbuf_new_from_file_at_scale (fn, width, height, 1, NULL);

    w = gdk_pixbuf_get_width (pb);
    h = gdk_pixbuf_get_height (pb);

    im = xmalloc (sizeof (image_t));

    im->src = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);

    cr = cairo_create (im->src);

    gdk_cairo_set_source_pixbuf (cr, pb, 0, 0);

    cairo_paint (cr);

    cairo_destroy (cr);

    g_object_unref (pb);


    return im;
}

image_t *image_create_from_resource (const char *res,
                                             int width, int height) {
    GdkPixbuf *pb = NULL;
    image_t *im = NULL;
    cairo_t *cr;

    int w, h;
    unsigned char *data = NULL;

    pb = gdk_pixbuf_new_from_resource_at_scale (res, width, height, 1, NULL);

    w = gdk_pixbuf_get_width (pb);
    h = gdk_pixbuf_get_height (pb);

    im = xmalloc (sizeof (image_t));

    im->src = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);

    cr = cairo_create (im->src);

    gdk_cairo_set_source_pixbuf (cr, pb, 0, 0);

    cairo_paint (cr);

    cairo_destroy (cr);

    g_object_unref (pb);


    return im;
}




image_t *image_ref (image_t *im) {
    im->src = cairo_surface_reference (im->src);
    return im;
}

void image_unref (image_t *im) {
    int ct = cairo_surface_get_reference_count (im->src);
    cairo_surface_destroy (im->src);
    if (ct == 1) 
        xfree (im);
}


int image_get_width (image_t *im) {
    return cairo_image_surface_get_width (im->src);
}

int image_get_height (image_t *im) {
    return cairo_image_surface_get_height (im->src);
}

void image_paint (image_t *im, canvas_t *ca) {
    cairo_set_source_surface (ca->cr, im->src, 0, 0);
    cairo_paint (ca->cr);
}


