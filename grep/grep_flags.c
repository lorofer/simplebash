#include "grep_flags.h"

int set_grep_flags(int argc, char *argv[], struct grep_flags *flags,
                   char **regex_pattern) {
  int error = 0;

  int res = 0;
  while ((res = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (res) {
      case 'e':
        *regex_pattern = optarg;
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'f':
        flags->f = 1;

        FILE *file = fopen(optarg, "r");
        if (file != NULL) {
          char *buffer = NULL;
          size_t size = 0;
          if (getline(&buffer, &size, file) != -1) {
            strcpy(optarg, buffer);
            *regex_pattern = optarg;
          }
          free(buffer);
          fclose(file);
        }
        break;
      case 'o':
        flags->o = 1;
        break;
      default:
        error = 1;
        break;
    }
  }

  return error;
}