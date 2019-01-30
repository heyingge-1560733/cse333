// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>" [legal/copyright]
// This program connects (via TCP) to the server on the supplied hostname
// and port. Once connected, the program reads the bytes from the local file,
// and it writes those bytes over the TCP connection

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>

#include <iostream>

#include "./network.h"

#define BUFFER_SIZE 1024

// print error message
void Usage(char*);

int main(int argc, char** argv) {
  if (argc != 4) {
    Usage(argv[0]);
  }

  unsigned short port = 0;
  if (sscanf(argv[2], "%hu", &port) != 1) {
    Usage(argv[0]);
  }

  // Get an appropriate sockaddr structure.
  struct sockaddr_storage addr;
  size_t addrlen;
  if (!LookupName(argv[1], port, &addr, &addrlen)) {
    Usage(argv[0]);
  }

  // Create the socket.
  int socket_fd = socket(addr.ss_family, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    std::cerr << "socket() failed: " << strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  // returns 0 on success, -1 on failure (errno set)
  if (connect(socket_fd, reinterpret_cast<sockaddr *>(&addr), addrlen) == -1) {
    std::cerr << "connect() failed: " << strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  int local_fd = open(argv[3], O_RDONLY);
  if (local_fd == -1) {
    perror("open failed");
    exit(EXIT_FAILURE);
  }

  char buf[BUFFER_SIZE];
  int bytes_read;
  while (1) {
    bytes_read = read(local_fd, buf, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
      if (errno != EINTR) {
        // a real error happened, so return an error result
        std::cerr << "read() failed: " << strerror(errno) << std::endl;
        close(local_fd);
        close(socket_fd);
        return EXIT_FAILURE;
      }
      // EINTR happened, so do nothing and try again
      continue;
    } else if (bytes_read == 0) {
      break;  // EOF reached, so stop reading
    } else {
      buf[bytes_read] = '\0';  // set EOF char
      int bytes_left = bytes_read;
      while (bytes_left > 0) {
        int bytes_written = write(socket_fd, buf +
                                 (bytes_read - bytes_left), bytes_left);
        if (bytes_written == -1) {
          if (errno != EINTR) {
            // a real error happened, so return an error result
            std::cerr << "write() failed: " << strerror(errno) << std::endl;
            close(local_fd);
            close(socket_fd);
            return EXIT_FAILURE;
          }
          // EINTR happened, so do nothing and try again
          continue;
        } else if (bytes_written == 0) {
          // EOF reached, so stop reading
          break;
        }
        bytes_left -= bytes_written;  // update bytes left to write
      }
    }
  }
  close(local_fd);
  close(socket_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " hostname port" << std::endl;
  exit(EXIT_FAILURE);
}

void PrintOut(int fd, struct sockaddr *addr, size_t addrlen) {
  std::cout << "Socket [" << fd << "] is bound to:" << std::endl;
  if (addr->sa_family == AF_INET) {
    // Print out the IPV4 address and port

    char astring[INET_ADDRSTRLEN];
    struct sockaddr_in *in4 = reinterpret_cast<struct sockaddr_in *>(addr);
    inet_ntop(AF_INET, &(in4->sin_addr), astring, INET_ADDRSTRLEN);
    std::cout << " IPv4 address " << astring;
    std::cout << " and port " << ntohs(in4->sin_port) << std::endl;

  } else if (addr->sa_family == AF_INET6) {
    // Print out the IPV6 address and port

    char astring[INET6_ADDRSTRLEN];
    struct sockaddr_in6 *in6 = reinterpret_cast<struct sockaddr_in6 *>(addr);
    inet_ntop(AF_INET6, &(in6->sin6_addr), astring, INET6_ADDRSTRLEN);
    std::cout << " IPv6 address " << astring;
    std::cout << " and port " << ntohs(in6->sin6_port) << std::endl;

  } else {
    std::cout << " ???? address and port ????" << std::endl;
  }
}

void PrintReverseDNS(struct sockaddr *addr, size_t addrlen) {
  char hostname[1024];  // ought to be big enough.
  if (getnameinfo(addr, addrlen, hostname, 1024, nullptr, 0, 0) != 0) {
    sprintf(hostname, "[reverse DNS failed]");
  }
  std::cout << " DNS name: " << hostname << std::endl;
}

void PrintServerSide(int client_fd, int sock_family) {
  char hname[1024];
  hname[0] = '\0';

  std::cout << "Server side interface is ";
  if (sock_family == AF_INET) {
    // The server is using an IPv4 address.
    struct sockaddr_in srvr;
    socklen_t srvrlen = sizeof(srvr);
    char addrbuf[INET_ADDRSTRLEN];
    getsockname(client_fd, (struct sockaddr *) &srvr, &srvrlen);
    inet_ntop(AF_INET, &srvr.sin_addr, addrbuf, INET_ADDRSTRLEN);
    std::cout << addrbuf;
    // Get the server's dns name, or return it's IP address as
    // a substitute if the dns lookup fails.
    getnameinfo((const struct sockaddr *) &srvr,
                srvrlen, hname, 1024, nullptr, 0, 0);
    std::cout << " [" << hname << "]" << std::endl;
  } else {
    // The server is using an IPv6 address.
    struct sockaddr_in6 srvr;
    socklen_t srvrlen = sizeof(srvr);
    char addrbuf[INET6_ADDRSTRLEN];
    getsockname(client_fd, (struct sockaddr *) &srvr, &srvrlen);
    inet_ntop(AF_INET6, &srvr.sin6_addr, addrbuf, INET6_ADDRSTRLEN);
    std::cout << addrbuf;
    // Get the server's dns name, or return it's IP address as
    // a substitute if the dns lookup fails.
    getnameinfo((const struct sockaddr *) &srvr,
                srvrlen, hname, 1024, nullptr, 0, 0);
    std::cout << " [" << hname << "]" << std::endl;
  }
}

int Listen(char *portnum, int *sock_family) {
  // Populate the "hints" addrinfo structure for getaddrinfo().
  // ("man addrinfo")
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET6;       // IPv6 (also handles IPv4 clients)
  hints.ai_socktype = SOCK_STREAM;  // stream
  hints.ai_flags = AI_PASSIVE;      // use wildcard "in6addr_any" address
  hints.ai_flags |= AI_V4MAPPED;    // use v4-mapped v6 if no v6 found
  hints.ai_protocol = IPPROTO_TCP;  // tcp protocol
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  // Use argv[1] as the string representation of our portnumber to
  // pass in to getaddrinfo().  getaddrinfo() returns a list of
  // address structures via the output parameter "result".
  struct addrinfo *result;
  int res = getaddrinfo(nullptr, portnum, &hints, &result);

  // Did addrinfo() fail?
  if (res != 0) {
    std::cerr << "getaddrinfo() failed: ";
    std::cerr << gai_strerror(res) << std::endl;
    return -1;
  }

  // Loop through the returned address structures until we are able
  // to create a socket and bind to one.  The address structures are
  // linked in a list through the "ai_next" field of result.
  int listen_fd = -1;
  for (struct addrinfo *rp = result; rp != nullptr; rp = rp->ai_next) {
    listen_fd = socket(rp->ai_family,
                       rp->ai_socktype,
                       rp->ai_protocol);
    if (listen_fd == -1) {
      // Creating this socket failed.  So, loop to the next returned
      // result and try again.
      std::cerr << "socket() failed: " << strerror(errno) << std::endl;
      listen_fd = -1;
      continue;
    }

    // Configure the socket; we're setting a socket "option."  In
    // particular, we set "SO_REUSEADDR", which tells the TCP stack
    // so make the port we bind to available again as soon as we
    // exit, rather than waiting for a few tens of seconds to recycle it.
    int optval = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof(optval));

    // Try binding the socket to the address and port number returned
    // by getaddrinfo().
    if (bind(listen_fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      // Bind worked!  Print out the information about what
      // we bound to.
      PrintOut(listen_fd, rp->ai_addr, rp->ai_addrlen);

      // Return to the caller the address family.
      *sock_family = rp->ai_family;
      break;
    }

    // The bind failed.  Close the socket, then loop back around and
    // try the next address/port returned by getaddrinfo().
    close(listen_fd);
    listen_fd = -1;
  }

  // Free the structure returned by getaddrinfo().
  freeaddrinfo(result);

  // If we failed to bind, return failure.
  if (listen_fd == -1)
    return listen_fd;

  // Success. Tell the OS that we want this to be a listening socket.
  if (listen(listen_fd, SOMAXCONN) != 0) {
    std::cerr << "Failed to mark socket as listening: ";
    std::cerr << strerror(errno) << std::endl;
    close(listen_fd);
    return -1;
  }

  // Return to the client the listening file descriptor.
  return listen_fd;
}
