/*
Copyright 2017 Soramitsu Co., Ltd.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef MESSENGER_CLIENT_H
#define MESSENGER_CLIENT_H

#include <messenger.grpc.pb.h>

using namespace grpc;

class MessengerClient {
 public:
  MessengerClient(std::string &address)
      : stub_(messenger::Messenger::NewStub(grpc::CreateChannel(
            address, grpc::InsecureChannelCredentials()))) {}

  std::string doRequest(std::string &requestString) {
    ClientContext context;
    messenger::Request request;
    request.set_query(requestString);
    messenger::Reply reply;
    Status status = stub_->SendMessage(&context, request, &reply);
    if (status.ok()) {
      return reply.response();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<messenger::Messenger::Stub> stub_;
};

#endif  // MESSENGER_CLIENT_H