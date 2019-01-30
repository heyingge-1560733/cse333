/*
 * Copyright ©2018 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./CSE333.h"

void VerificationFailure(const char *exp, const char *file,
                      const char *baseFile, int line) {
  if (!strcmp(file, baseFile)) {
    fprintf(stderr,
            "Verify333(%s) failed in file %s, line %d\n", exp, file, line);
  } else {
    fprintf(stderr,
            "Verify333(%s) failed in file %s (included from %s), line %d\n",
            exp, file, baseFile, line);
  }
  exit(EXIT_FAILURE);
}
