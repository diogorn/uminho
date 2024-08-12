#ifndef RESULTS_H
#define RESULTS_H

#include <glib.h>

int queries_file(Stats s, int argc,char *file_path);

GSList* parseLine(const char *input);
Date get_date(Date date);

#endif