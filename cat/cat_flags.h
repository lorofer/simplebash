#ifndef cat_flags_h
#define cat_flags_h

#include <getopt.h>
#include <stdio.h>

struct cat_flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
};

int set_cat_flags(int, char **, struct cat_flags *, struct option *);
void n_flag(char, int *, int *);
void b_flag(char, char, int *, int *);
void e_flag(char);
int t_flag(char);
int v_flag(char);

#endif