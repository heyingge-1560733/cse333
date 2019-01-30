// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>" [legal/copyright]
// This program is the header file for network.cc.

#ifndef _NETWORK_H_
#define _NETWORK_H_

// Figure out the IP address and port on which to listen;
// Create a socket;
// bind the socket to the address(es) and port;
// Tell the socket to listen for incoming clients;
int Listen(char *portnum, int *sock_family);

#endif  // _NETWORK_H_
