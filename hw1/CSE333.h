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

#ifndef _HW1_CSE333_H_
#define _HW1_CSE333_H_

#include <stdint.h>  // for uint32_t, etc.

// We abstract the idea of some quantities into user defined types
//  so  that we could, in theory, easily change between uint32_t and
// uint64_t realizations, say.

typedef uint32_t HWSize_t;   // for sizes of containers and indices into containers

// A wrapper for assert that permits side-effects within the
// Verify333() statement.  Borrowed from:
//
//   http://www.acm.uiuc.edu/sigops/roll_your_own/2.a.html

void VerificationFailure(const char *exp, const char *file,
                         const char *basefile, int line);

#define Verify333(exp) if (exp) ; \
  else VerificationFailure(#exp, __FILE__, __BASE_FILE__, __LINE__)

#endif  // _HW1_CSE333_H_
