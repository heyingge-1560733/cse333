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

#ifndef _HW4_HTTPSERVER_H_
#define _HW4_HTTPSERVER_H_

#include <stdint.h>
#include <string>
#include <list>

#include "./ThreadPool.h"
#include "./ServerSocket.h"

namespace hw4 {

// The HttpServer class contains the main logic for the web server.
class HttpServer {
 public:
  // Creates a new HttpServer object for port "port" and serving
  // files out of path "staticfile_dirpath".  The indices for
  // query processing are located in the "indices" list. The constructor
  // does not do anything except memorize these variables.
  explicit HttpServer(uint16_t port,
                      std::string staticfile_dirpath,
                      std::list<std::string> indices)
    : ss_(port), staticfile_dirpath_(staticfile_dirpath),
    indices_(indices), kNumThreads(100) { }

  // The destructor closes the listening socket if it is open and
  // also kills off any threads in the threadpool.
  virtual ~HttpServer(void) { }

  // Creates a listening socket for the server and launches it, accepting
  // connections and dispatching them to worker threads.  Returns
  // "true" if the server was able to start and run, "false" otherwise.
  // The server continues to run until a kill command is used to send
  // a SIGTERM signal to the server process (i.e., kill pid).
  bool Run(void);

 private:
  ServerSocket ss_;
  std::string staticfile_dirpath_;
  std::list<std::string> indices_;
  const int kNumThreads;
};

class HttpServerTask : public ThreadPool::Task {
 public:
  explicit HttpServerTask(ThreadPool::thread_task_fn f)
    : ThreadPool::Task(f) { }

  int client_fd;
  uint16_t cport;
  std::string caddr, cdns, saddr, sdns;
  std::string basedir;
  std::list<std::string> *indices;
};

}  // namespace hw4

#endif  // _HW4_HTTPSERVER_H_
