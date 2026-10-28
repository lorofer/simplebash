#include "cat_flags.h"

int set_cat_flags(int argc, char *argv[], struct cat_flags *flags,
                  struct option *longopts) {
  int error = 0;

  int res = 0;
  while ((res = getopt_long(argc, argv, "bEensTtv", longopts, NULL)) != -1) {
    switch (res) {
      case 'b':
        flags->b = 1;
        break;
      case 'E':
        flags->e = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'T':
        flags->t = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      default:
        error = 1;
        break;
    }
  }

  if (flags->b && flags->n) {
    flags->n = 0;
  }

  return error;
}

void n_flag(char curr_ch, int *prev_str_number, int *curr_str_number) {
  if (*prev_str_number < *curr_str_number) {
    printf("%6d\t", *curr_str_number);
    (*prev_str_number)++;
  }
  if (curr_ch == '\n') {
    (*curr_str_number)++;
  }
}

void b_flag(char curr_ch, char prev_ch, int *prev_str_number,
            int *curr_str_number) {
  if (curr_ch != '\n' && *prev_str_number < *curr_str_number) {
    printf("%6d\t", *curr_str_number);
    (*prev_str_number)++;
  } else if (curr_ch == '\n' && !(prev_ch == '\n' || prev_ch == 0)) {
    (*curr_str_number)++;
  }
}

void e_flag(char curr_ch) {
  if (curr_ch == '\n') {
    putchar('$');
  }
}

int t_flag(char curr_ch) {
  int char_has_been_output = 0;
  if (curr_ch == '\t') {
    printf("^I");
    char_has_been_output = 1;
  }
  return char_has_been_output;
}

int v_flag(char curr_ch) {
  int char_has_been_output = 0;
  if (curr_ch < 32 && curr_ch >= 0 && curr_ch != '\n' && curr_ch != '\t') {
    printf("^%c", curr_ch + 64);
    char_has_been_output = 1;
  } else if (curr_ch == 127) {
    printf("^?");
    char_has_been_output = 1;
  }
  return char_has_been_output;
}