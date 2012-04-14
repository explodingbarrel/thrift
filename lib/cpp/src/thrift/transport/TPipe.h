/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef _THRIFT_TRANSPORT_TPIPE_H_
#define _THRIFT_TRANSPORT_TPIPE_H_ 1
#ifdef _WIN32

#include "TTransport.h"
#include "TVirtualTransport.h"

namespace apache { namespace thrift { namespace transport {

/**
 * Windows Pipes implementation of the TTransport interface.
 *
 */
class TPipe : public TVirtualTransport<TPipe> {
 public:

  // Constructs a new pipe object.
  TPipe();
  // Named pipe constructors -
  TPipe(HANDLE hPipe);
  TPipe(std::string path);
  // Anonymous pipe -
  TPipe(HANDLE hPipeRd, HANDLE hPipeWrt);

  // Destroys the pipe object, closing it if necessary.
  virtual ~TPipe();

  // Returns whether the pipe is open & valid.
  virtual bool isOpen();

  // Checks whether more data is available in the pipe.
  virtual bool peek();

  // Creates and opens the named/anonymous pipe.
  virtual void open();

  // Shuts down communications on the pipe.
  virtual void close();

  // Reads from the pipe.
  virtual uint32_t read(uint8_t* buf, uint32_t len);

  // Writes to the pipe.
  virtual void write(const uint8_t* buf, uint32_t len);


  //Accessors
  std::string getPipename();
  void setPipename(std::string pipename);
  HANDLE getPipeHandle(); //doubles as the read handle for anon pipe
  void setPipeHandle(HANDLE pipehandle);
  HANDLE getWrtPipeHandle();
  void setWrtPipeHandle(HANDLE pipehandle);
  long getConnectTimeout();
  void setConnectTimeout(long seconds);

 private:
  std::string pipename_;
  //Named pipe handles are R/W, while anonymous pipes are one or the other (half duplex).
  HANDLE hPipe_, hPipeWrt_;
  long TimeoutSeconds_;
  bool isAnonymous;

};

}}} // apache::thrift::transport

#endif //_WIN32
#endif // #ifndef _THRIFT_TRANSPORT_TPIPE_H_

