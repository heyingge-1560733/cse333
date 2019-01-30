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

unsigned int hw1_maxpoints = 230;
unsigned int hw1_points = 0;

void HW1ResetPoints() {
  hw1_points = 0;
}

void HW1Addpoints(unsigned int points) {
  hw1_points += points;
  cout << " (" << hw1_points << "/" << hw1_maxpoints << ")" << endl;
}

class HW1Environment : public ::testing::Environment {
 public:

  virtual void SetUp() {
    // Code here is run once for the entire test suite.
    cout << "HW1: there are " << hw1_maxpoints;
    cout << " points available." << endl;
  }
  virtual void TearDown() {
    // Code here is run once for the entire test suite.
    cout << endl;
    cout << "You earned " << hw1_points << " out of ";
    cout << hw1_maxpoints << " points available (";
    cout << ((100.0*hw1_points) / hw1_maxpoints) << "%)" << endl;
    cout << endl;
  }
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new HW1Environment);
  return RUN_ALL_TESTS();
}
