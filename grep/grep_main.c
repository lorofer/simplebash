#include "grep_main.h"

int main(int argc, char *argv[]) {
  int error = 0;

  struct grep_flags flags = {
      .i = 0, .v = 0, .c = 0, .l = 0, .n = 0, .h = 0, .s = 0, .f = 0, .o = 0};
  char *regex_pattern = NULL;

  if ((error = set_grep_flags(argc, argv, &flags, &regex_pattern)) == 1) {
    fprintf(stderr, "Flags error");
  }

  int files_index = optind;
  if (!error && regex_pattern == NULL) {
    regex_pattern = argv[optind];
    files_index++;
  }

  if (!error && files_index == argc) {
    fprintf(stderr, "Files are not specified");
    error = 1;
  }

  if (!error) {
    error = files_processing(argc, argv, flags, regex_pattern, files_index);
  }

  return error;
}