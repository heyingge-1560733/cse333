// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program accepts a filename as a single command-line argument.
// Then reads the file, copying the contents of the file to stdout
// in reverse order, character by character.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#define READBUFSIZE 1

int main(int argc, char** argv) {
  if (argc != 2) {
    // check the number of argument to be exactly 2
    printf("ERROR: Invalid input -- Need to include one file name.\n");
    return EXIT_FAILURE;
  }

  // Open the input file
  FILE* fin = fopen(argv[1], "rb");
  if (fin == NULL) {
    fprintf(stderr, "%s -- ", argv[1]);
    perror("fopen for read failed");
    return EXIT_FAILURE;
  }

  if (fseek(fin, 0, SEEK_END) != 0) {
    fprintf(stderr, "%s -- ", argv[1]);
    perror("fseek for read failed");
    return EXIT_FAILURE;
  }

  long size = ftell(fin) - 1;  // get rid of the EOF byte
  char readbuf[READBUFSIZE];

  // print contents of the file to stdout in reverse
  // order, character by character
  for (int64_t i = (int64_t)size - 1; i >= 0; i--) {
    if (fseek(fin, i, SEEK_SET) != 0) {
      fprintf(stderr, "%s -- ", argv[1]);
      perror("fseek for read failed");
      return EXIT_FAILURE;
    }
    fread((void*)readbuf, 1, READBUFSIZE, fin);
    printf("%c", readbuf[0]);
  }

  // Test to see if we encountered an error while reading
  if (ferror(fin)) {
    perror("fread failed");
    return EXIT_FAILURE;
  }

  fclose(fin);

  return EXIT_SUCCESS;
}
