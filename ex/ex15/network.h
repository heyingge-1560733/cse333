// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>" [legal/copyright]
// This program is the header file for network.cc.

#ifndef _NETWORK_H_
#define _NETWORK_H_

// establishes a connection to a remote host
bool Connect(const struct sockaddr_storage&, const size_t&, int*);

// figure out what IP address and port to talk to
bool LookupName(char*, uint16_t, struct sockaddr_storage*, size_t*);

#endif
