#include "plugin.h"
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

line_count = 0;

typedef struct _txt_page {
  char **data;
} txt_page_t;

typedef struct _txt_document {
  txt_page_t *pages;
} txt_document_t;

// register the plugin
ZATHURA_PLUGIN_REGISTER_WITH_FUNCTIONS (
  "txt",
  0, 1, 0,
  ZATHURA_PLUGIN_FUNCTIONS({
    .document_open            = txt_document_open,
    .document_free            = txt_document_free,
    .page_init                = txt_page_init,
    .page_clear               = txt_page_clear,
    .page_render_cairo        = txt_page_render_cairo,
  }),
  ZATHURA_PLUGIN_MIMETYPES ({"text/plain"})
)

zathura_error_t txt_document_open(zathura_document_t *document) {
  zathura_error_t error = ZATHURA_ERROR_OK;
  txt_document_t *txt_document = g_malloc0(sizeof(txt_document_t));
  txt_document->pages = (txt_page_t *)malloc(sizeof(txt_page_t));
  txt_document->pages[0].data = malloc(30*sizeof(char*));
  const char* path = zathura_document_get_path(document);
  FILE *fin = fopen(path, "r");
  char line[2048];
  while(fgets(line, 2048, fin) != NULL) {
    printf("Hello\n");
    if (line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
    txt_document->pages[0].data[line_count] = strdup(line);
    line_count++;
  }
  fclose(fin);
  zathura_document_set_number_of_pages(document, 1);
  zathura_document_set_data(document, txt_document);
  return error;
}

zathura_error_t txt_document_free(zathura_document_t *document, void *txt_document) {
  free(((txt_document_t *)txt_document)->pages);
  g_free((txt_document_t *)txt_document);
  return ZATHURA_ERROR_OK;
}

zathura_error_t txt_page_init(zathura_page_t *page) {
  zathura_document_t *document = zathura_page_get_document(page);
  txt_document_t *txt_document = zathura_document_get_data(document);
  zathura_page_set_width(page, 500);
  zathura_page_set_height(page, 500);
  zathura_page_set_data(page, txt_document->pages);
  return ZATHURA_ERROR_OK;
}

zathura_error_t txt_page_clear(zathura_page_t *page, void *txt_page) {
  free(((txt_page_t*)page)->data);
  return ZATHURA_ERROR_OK;
}

zathura_error_t txt_page_render_cairo(zathura_page_t *page, void *txt_page, cairo_t *cairo, bool printing) {
  zathura_document_t* document = zathura_page_get_document(page);
  cairo_move_to(cairo, 20, 30);
  for (int i = 0; i < line_count; i++) {
    cairo_move_to(cairo, 20, 30+i*15);
    cairo_show_text(cairo, ((txt_page_t *)txt_page)->data[i]);
  }
  return ZATHURA_ERROR_OK;
}
