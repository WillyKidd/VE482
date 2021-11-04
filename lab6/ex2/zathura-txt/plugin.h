#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdbool.h>
#include <zathura/plugin-api.h>
#include <cairo/cairo.h>

extern int line_count;
/**
 * initialize all necessary objects and values 
 * that we are going to need for the future use of the plugin
 */
GIRARA_HIDDEN zathura_error_t txt_document_open(zathura_document_t *document);

GIRARA_HIDDEN zathura_error_t txt_document_free(zathura_document_t *document, void *txt_document);

GIRARA_HIDDEN zathura_error_t txt_page_init(zathura_page_t *page);

GIRARA_HIDDEN zathura_error_t txt_page_clear(zathura_page_t *page, void *txt_page);

GIRARA_HIDDEN zathura_error_t txt_page_render_cairo(zathura_page_t *page, void *txt_page, cairo_t *cairo, bool printing);

#endif // PLUGIN_H
