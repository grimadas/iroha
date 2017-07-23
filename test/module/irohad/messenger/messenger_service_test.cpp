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

#include <gtest/gtest.h>
#include <main/server_runner.hpp>
#include "consensus_utils/messenger_client.hpp"
#include "consensus_utils/messenger_server.hpp"

#include <atomic>
#include <thread>

using namespace grpc;

class MessengerServiceTest : public ::testing::Test {
 private:
  ServerBuilder builder;
  MessengerServerImpl service;
  std::unique_ptr<Server> server;

 public:
  virtual void SetUp() {
    std::string server_address("0.0.0.0:50051");
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    server = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;
  }

  virtual void TearDown() {}
};

TEST_F(MessengerServiceTest, MessengerSync) {
  MessengerClient client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::string request("hi");
  std::string reply = client.doRequest(request);
  std::cout << "Answer received: " << reply << std::endl;
  ASSERT_EQ(reply, "hi!");
}
