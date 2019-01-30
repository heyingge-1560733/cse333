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
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

#define READLEN 1024

using std::map;
using std::string;

namespace hw4 {

bool HttpConnection::GetNextRequest(HttpRequest *request) {
  // Use "WrappedRead" to read data into the buffer_
  // instance variable.  Keep reading data until either the
  // connection drops or you see a "\r\n\r\n" that demarcates
  // the end of the request header.
  //
  // Once you've seen the request header, use ParseRequest()
  // to parse the header into the *request argument.
  //
  // Very tricky part:  clients can send back-to-back requests
  // on the same socket.  So, you need to preserve everything
  // after the "\r\n\r\n" in buffer_ for the next time the
  // caller invokes GetNextRequest()!

  // MISSING:
  int size;

  // if buffer_ does not contain end of header
  if (buffer_.find("\r\n\r\n") == string::npos) {
    while (1) {
      char buf[READLEN];
      int res = WrappedRead(fd_, reinterpret_cast<unsigned char *>(buf),
                            READLEN);

      if (res == 0) {  // EOF
        break;
      } else if (res == -1) {
        return false;  // error
      } else {
        size += res;  // update read bytes
        buffer_ += &buf[0];

        // found end of header, send request
        if (buffer_.find("\r\n\r\n") != string::npos)
          break;
        continue;
      }
    }
  }

  size_t pos = buffer_.find("\r\n\r\n");
  // fail to find end of header
  if (pos == string::npos)
    return false;

  // end of header is found
  *request = ParseRequest(pos);;
  buffer_.erase(0, pos + 4);

  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse &response) {
  std::string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         (unsigned char *) str.c_str(),
                         str.length());
  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(size_t end) {
  HttpRequest req;
  req.URI = "/";  // by default, get "/".

  // Get the header.
  std::string str = buffer_.substr(0, end);

  // Split the header into lines.  Extract the URI from the first line
  // and store it in req.URI.  For each additional line beyond the
  // first, extract out the header name and value and store them in
  // req.headers (i.e., req.headers[headername] = headervalue).
  // You should look at HttpResponse.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for (a) splitting
  // a string into lines on a "\r\n" delimiter, (b) trimming
  // whitespace from the end of a string, and (c) converting a string
  // to lowercase.

  // MISSING:
  // Split the header into lines by deliminator "\r\n"
  std::vector<string> lines;
  boost::algorithm::split(lines, str, boost::is_any_of("\r\n"),
                          boost::algorithm::token_compress_on);

  for (size_t i = 0; i < lines.size(); i++)
    // trimming whitespace from the end of a string
    boost::trim(lines[i]);

  std::vector<string> first_line;
  boost::algorithm::split(first_line, lines[0], boost::is_any_of(" "),
                          boost::algorithm::token_compress_on);

  req.URI = first_line[1];
  lines.erase(lines.begin());

  for (auto line : lines) {
    std::vector<std::string> header;
    // Split the header into lines by deliminator ": "
    boost::algorithm::split(header, line, boost::is_any_of(": "),
                            boost::algorithm::token_compress_on);

    string header_name = header[0];
    boost::algorithm::to_lower(header_name);

    // map header name to header value
    req.headers[header_name] = header[1];
  }

  return req;
}

}  // namespace hw4
