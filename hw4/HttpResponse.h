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

#ifndef _HW4_HTTPRESPONSE_H_
#define _HW4_HTTPRESPONSE_H_

#include <stdint.h>

#include <map>
#include <string>
#include <sstream>

using std::string;

namespace hw4 {

// This class represents the state of an HTTP response, including the
// headers and body.  Customers (primarily HttpServer.cc) create an
// instance of this class when preparing their response, and they
// use GenerateResponseString() to generate a string-representation
// ready for sending on a socket.
//
// A response has the following format:
//
// [http_protocol] [response_code] [message]\r\n
// [headername]: [headerval]\r\n
// [headername]: [headerval]\r\n
// ... more headers ...
// [headername]: [headerval]\r\n
// [body]
//
// e.g.:
//
// HTTP/1.1 200 OK\r\n
// Content-length: 10\r\n
// \r\n
// Hi there!!

class HttpResponse {
 public:
  HttpResponse() { }
  virtual ~HttpResponse(void) { }

  // The HTTP protocol string to pass back in the first line.
  std::string protocol;

  // The HTTP response code to pass back in the first line.
  uint16_t response_code;

  // The HTTP response code message to pass back in the first line.
  std::string message;

  // A map from header name to header value, representing
  // all of the headers we'll give back to the client.  Should
  // not contain "Content-length" -- we'll dynamically calculate
  // it inside GenerateReponseString().  The header names should
  // be properly capitalized.
  std::map<std::string, std::string> headers;

  // The body of the response.
  std::string body;

  // A method to generate a std::string of the HTTP response, suitable
  // for writing back to the client.  We automatically generate the
  // "Content-length:" header, and make that be the last header
  // in the block.  The value of the Content-length header is the
  // size of the response body (in bytes).
  std::string GenerateResponseString(void) const {
    std::stringstream header;
    std::map<std::string, std::string>::const_iterator it;

    header << protocol << " " << response_code << " " << message << "\r\n";
    for (it = headers.begin(); it != headers.end(); it++) {
      header << it->first << ": " << it->second << "\r\n";
    }
    header << "Content-length: " << body.size() << "\r\n";
    header << "\r\n";
    header << body;
    return header.str();
  }
};

}  // namespace hw4

#endif  // _HW4_HTTPRESPONSE_H_
