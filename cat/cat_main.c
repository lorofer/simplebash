#include "cat_main.h"

int main(int argc, char *argv[]) {
  int error = 0;

  struct cat_flags flags = {.b = 0, .e = 0, .n = 0, .s = 0, .t = 0, .v = 0};
  struct option long_options[] = {
      {"number-nonblank", 0, NULL, 'b'},
      {"number", 0, NULL, 'n'},
      {"squeeze-blank", 0, NULL, 's'},
  };

  if ((error = set_cat_flags(argc, argv, &flags, long_options)) == 1) {
    fprintf(stderr, "Flags error");
  }

  int file_index = optind;
  if (!error && (file_index == argc)) {
    fprintf(stderr, "Files are not specified");
    error = 1;
  }

  if (!error) {
    string_processing(argc, argv, file_index, flags);
  }

  return error;
}