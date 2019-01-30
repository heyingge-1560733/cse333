// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>" [legal/copyright]
// This program creates a TCP listening socket on the supplied port number.
// Once a client connects, the program reads data from the connected client
// socket and write it to stdout until there is no more data to read from
// the client.

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

// prints out error message
void Usage(char *progname);

// read data from client and print to stdout
void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family);

int main(int argc, char** argv) {
  if (argc != 2) {
    Usage(argv[0]);
  }

  // Expect the port number as a command line argument.
  if (argc != 2) {
    Usage(argv[0]);
  }

  int sock_family;
  int listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd <= 0) {
    // We failed to bind/listen to a socket.  Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    return EXIT_FAILURE;
  }

  // Loop forever, accepting a connection from a client and doing
  // an echo trick to it.
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    int client_fd = accept(listen_fd,
                           reinterpret_cast<struct sockaddr *>(&caddr),
                           &caddr_len);
    if (client_fd < 0) {
      if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
        continue;
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      break;
    }

    HandleClient(client_fd,
                 reinterpret_cast<struct sockaddr *>(&caddr),
                 caddr_len,
                 sock_family);
    break;
  }

  // Close file descriptor
  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " hostname port" << std::endl;
  exit(EXIT_FAILURE);
}

void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family) {
  char buf[BUFFER_SIZE];
  int bytes_read;

  while (1) {
    bytes_read = read(c_fd, buf, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
      if ((errno != EAGAIN) && (errno != EINTR)) {
        // a real error happened, so return an error result
        std::cout << " [Error on client socket: ";
        std::cout << strerror(errno) << "]" << std::endl;
        break;
      }
      // EINTR happened, so do nothing and try again
      continue;
    } else if (bytes_read == 0) {
      break;  // EOF reached, so stop reading
    } else {
      buf[bytes_read] = '\0';  // set EOF char
      int bytes_left = bytes_read;

      while (bytes_left > 0) {
        int bytes_written = write(1, buf +
                                 (bytes_read - bytes_left), bytes_left);
        if (bytes_written == -1) {
          if (errno != EINTR) {
            // a real error happened, so return an error result
            std::cerr << "write() failed: " << strerror(errno) << std::endl;
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

  close(c_fd);  // close the file descriptor
}
