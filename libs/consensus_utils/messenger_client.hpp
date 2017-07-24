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

#include <grpc++/grpc++.h>
#include <grpc/support/log.h>
#include <messenger.grpc.pb.h>
#include <messenger.pb.h>

using namespace grpc;

class MessengerClient {
 public:
  MessengerClient(std::string &address)
      : stub_(messenger::Messenger::NewStub(grpc::CreateChannel(
            address, grpc::InsecureChannelCredentials()))) {}

  void doRequest(std::string &requestString) {
    messenger::Request request;
    request.set_query(requestString);

    AsyncClientCall *call = new AsyncClientCall;
    call->response_reader =
        stub_->AsyncSendMessage(&call->context, request, &cq_);
    call->response_reader->Finish(&call->reply, &call->status, (void *)call);
  }

  std::string asyncCompleteRPC() {
    void *got_tag;
    bool ok = false;

    // Block until the next result is available in the completion queue "cq".
    while (cq_.Next(&got_tag, &ok)) {
      // The tag in this example is the memory location of the call object
      AsyncClientCall *call = static_cast<AsyncClientCall *>(got_tag);

      // Verify that the request was completed successfully. Note that "ok"
      // corresponds solely to the request for updates introduced by Finish().
      GPR_ASSERT(ok);

      std::string result;
      if (call->status.ok()) {
        result = call->reply.response();
      }

      else {
        result = "RPC failed";
      }

      // Once we're complete, deallocate the call object.
      delete call;
      return result;
    }
    return "Unexpected fail happened";
  }

 private:
  std::unique_ptr<messenger::Messenger::Stub> stub_;
  CompletionQueue cq_;

  struct AsyncClientCall {
    // Container for the data we expect from the server.
    messenger::Reply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // Storage for the status of the RPC upon completion.
    Status status;
    std::unique_ptr<ClientAsyncResponseReader<messenger::Reply>>
        response_reader;
  };
};

#endif  // MESSENGER_CLIENT_H