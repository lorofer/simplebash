#ifndef grep_flags_h
#define grep_flags_h

#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct grep_flags {
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

int set_grep_flags(int, char **, struct grep_flags *, char **);

#endif