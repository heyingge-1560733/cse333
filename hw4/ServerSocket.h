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

#ifndef _HW4_SERVERSOCKET_H_
#define _HW4_SERVERSOCKET_H_

#include <netdb.h>       // for AF_UNSPEC, AF_INET, AF_INET6
#include <stdint.h>      // for uint16_t, etc.
#include <sys/types.h>   // for AF_UNSPEC, AF_INET, AF_INET6
#include <sys/socket.h>  // for AF_UNSPEC, AF_INET, AF_INET6
#include <string>        // for std::string

namespace hw4 {

// A ServerSocket class abstracts away the messy details of creating a
// TCP listening socket at a specific port and on a (hopefully)
// externally visible IP address.  As well, a ServerSocket helps
// customers accept incoming client connections on the listening
// socket.
class ServerSocket {
 public:
  // This constructor creates a new ServerSocket object and associates
  // it with the provided port number.  The constructor doesn't create
  // a socket yet; it just memorizes the given port.
  explicit ServerSocket(uint16_t port);

  // The destructor closes the listening socket if it is open.
  virtual ~ServerSocket();

  // This function causes the ServerSocket to attempt to create a
  // listening socket and to bind it to the given port number on
  // whatever IP address the host OS recommends for us.  The caller
  // provides:
  //
  // - ai_family: whether to create an IPv4, IPv6, or "either" listening
  //   socket.  To specify IPv4, customers pass in AF_INET.  To specify
  //   IPv6, customers pass in AF_INET6.  To specify "either" (which
  //   leaves it up to BindAndListen() to pick, in which case it will
  //   typically try IPv4 first), customers pass in AF_UNSPEC.  AF_INET6
  //   can handle IPv6 and IPv4 clients on POSIX systems, while AF_UNSPEC
  //   might pick IPv4 and not be able to accept IPv6 connections.
  //
  // On failure this function returns false.  On success, it returns
  // true, sets listen_sock_fd_ to be the file descriptor for the
  // listening socket, and also returns (via an output parameter):
  //
  // - listen_fd: the file descriptor for the listening socket.
  bool BindAndListen(int ai_family, int *listen_fd);

  // This function causes the ServerSocket to attempt to accept
  // an incoming connection from a client.  On failure, returns false.
  // On success, it returns true, and also returns (via output
  // parameters) the following:
  //
  // - accepted_fd: the file descriptor for the new client connection.
  //   The customer is responsible for close()'ing this socket when it
  //   is done with it.
  //
  // - client_addr: a C++ string object containing a printable
  //   representation of the IP address the client connected from.
  //
  // - client_port: a uint16_t containing the port number the client
  //   connected from.
  //
  // - client_dnsname: a C++ string object containing the DNS name
  //   of the client.
  //
  // - server_addr: a C++ string object containing a printable
  //   representation of the server IP address for the connection.
  //
  // - server_dnsname: a C++ string object containing the DNS name
  //   of the server.
  bool Accept(int *accepted_fd,
              std::string *client_addr, uint16_t *client_port,
              std::string *client_dnsname, std::string *server_addr,
              std::string *server_dnsname);

 private:
  uint16_t port_;
  int listen_sock_fd_;
  int sock_family_;  // either AF_INET or AF_INET6 for ipv4 or ipv6/v4
};

}  // namespace hw4

#endif  // _HW4_SERVERSOCKET_H_
