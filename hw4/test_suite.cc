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

#include "gtest/gtest.h"

using std::cout;
using std::endl;

unsigned int hw4_maxpoints = 140;
unsigned int hw4_points = 0;

void HW4ResetPoints() {
  hw4_points = 0;
}

void HW4Addpoints(unsigned int points) {
  hw4_points += points;
  cout << " (" << hw4_points << "/" << hw4_maxpoints << ")" << endl;
}

class HW4Environment : public ::testing::Environment {
 public:

  virtual void SetUp() {
    // Code here is run once for the entire test suite.
    cout << "HW4: there are " << hw4_maxpoints;
    cout << " points available." << endl;
  }
  virtual void TearDown() {
    // Code here is run once for the entire test suite.
    cout << endl;
    cout << "You earned " << hw4_points << " out of ";
    cout << hw4_maxpoints << " points available (";
    cout << ((100.0*hw4_points) / hw4_maxpoints) << "%)" << endl;
    cout << endl;
  }
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new HW4Environment);
  return RUN_ALL_TESTS();
}
