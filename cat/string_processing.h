#ifndef string_processing_h
#define string_processing_h

#include <stdio.h>

#include "cat_flags.h"

void string_processing(int, char **, int, struct cat_flags);
void char_conversion(struct cat_flags, char, const char *, int *, int *);

#endif