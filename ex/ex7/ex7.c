// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program accepts a directory name as a command-line argument,
// scans through the directory looking for filenames that end in the
// four characters ".txt", reads the contents of those files and copy
// the contents to stdout

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/dir.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define buf_size 1024  // size of buffer

// concatenate the two strings and print all the files in this file
static void ReadPrint(char* dir, char* filename);

// print the content in the file in the argument to stdouts
static void PrintFile(char* dir_file);

int main(int argc, char **argv) {
  // verify valid input
  if (argc != 2) {
    fprintf(stderr, "Invalid number of argument. Should be 2.");
    return EXIT_FAILURE;
  }

  DIR *dirptr = opendir(argv[1]);

  if (dirptr == NULL) {
    perror("invalid directory");
    exit(EXIT_FAILURE);
  }

  struct dirent *entry = readdir(dirptr);
  while (entry != NULL) {
    if (strlen(entry->d_name) >= 4 &&  // filename length at least 4
       (strcmp(entry->d_name + (strlen(entry->d_name)-4), ".txt") == 0))
      // file name matches the form "*.txt"
      ReadPrint(argv[1], entry->d_name);

    entry = readdir(dirptr);
  }
}

static void ReadPrint(char* dirname, char* filename) {
  uint16_t total_length = strlen(dirname) + strlen(filename);
  char *dir_file = (char*) malloc(sizeof(char) * (total_length + 2));
  if (dir_file == NULL) {
    perror("out of memory");
    exit(EXIT_FAILURE);
  }

  // concatenate directory name and file name with a "/" between
  snprintf(dir_file, total_length + 2, "%s/%s", dirname, filename);

  PrintFile(dir_file);
  free(dir_file);  // success
}

static void PrintFile(char* dir_file) {
  int file = open(dir_file, O_RDONLY);
  if (file == -1) {
    perror("can't open file");
    exit(EXIT_FAILURE);
  }

  char buf[1024];
  int result = 0;
  while (1) {
    result = read(file, buf, buf_size - result);
    if (result == 0) {
      break;
    }

    if (result == -1) {
      if (errno != EINTR) {
        // a real error happened, so return an error result
        perror("read failed");
        exit(EXIT_FAILURE);
      }
      continue;  // EINTR happened, so do nothing and try again
    }

    if (fwrite(buf, 1, result, stdout) < result) {
      perror("fwrite failed");
      exit(EXIT_FAILURE);
    }
  }
  close(file);
}
