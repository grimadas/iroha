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
#include <grpc++/grpc++.h>
#include "consensus_utils/messenger_client.hpp"
#include <consensus_utils/messenger_server_runner.hpp>
#include <model/peer.hpp>

using namespace grpc;

class MessengerServiceTest : public ::testing::Test {
 private:
  MessengerServerRunner runner_;

 public:
  virtual void SetUp() {
    runner_.run("0.0.0.0:50051");
  }

  virtual void TearDown() {}
};

TEST_F(MessengerServiceTest, MessengerSync) {
  iroha::model::Peer peer;
  peer.address = "localhost:50051";
  MessengerClient client(peer.address);
  std::string request("hi");
  std::string reply = client.doRequest(request);
  std::cout << "Answer received: " << reply << std::endl;
  ASSERT_EQ(reply, "hi!");
}
