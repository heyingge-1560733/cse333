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

#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "./HttpUtils.h"
#include "./ServerSocket.h"
#include "./ThreadPool.h"
#include "./test_suite.h"

#include "./test_serversocket.h"

namespace hw4 {

static uint16_t portnum;

void TestSSThreadFn(ThreadPool::Task *t) {
  // Create the server socket.
  int listen_fd;
  std::cout << "Creating ss on " << portnum << std::endl;
  ServerSocket ss(portnum);
  std::cout << "Doing BAL" << std::endl;
  ASSERT_TRUE(ss.BindAndListen(AF_INET6, &listen_fd));

  // Accept a connection.
  int accept_fd;
  uint16_t cport;
  std::string caddr, cdns, saddr, sdns;
  std::cout << "Doing accept..." << std::endl;
  ASSERT_TRUE(ss.Accept(&accept_fd, &caddr, &cport, &cdns, &saddr, &sdns));

  // It worked!
  std::cout << "Accept succeeded." << std::endl;
  close(accept_fd);
  return;
}

TEST_F(Test_ServerSocket, TestServerSocketBasic) {
  // Create a threadpool, and dispatch a thread to go listen on a
  // server socket on a random port.
  portnum = GetRandPort();
  ThreadPool tp(2);
  ThreadPool::Task tsk(&TestSSThreadFn);
  tp.Dispatch(&tsk);

  // Give the thread a chance to create the socket.
  sleep(1);

  // Connect to the socket, using hw2's SocketClient.
  std::cout << "attempting to connect to 127.0.0.1 port "
            << portnum << std::endl;
  int cfd = -1;
  ASSERT_TRUE(ConnectToServer("127.0.0.1", portnum, &cfd));
  ASSERT_LE(0, cfd);
  HW4Addpoints(20);
}

}  // namespace hw4
