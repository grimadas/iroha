/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_BLOCK_SERIALIZER_HPP
#define IROHA_BLOCK_SERIALIZER_HPP

#include <model/block.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include <model/commands/add_asset_quantity.hpp>
#include <model/commands/add_peer.hpp>
#include <model/commands/add_signatory.hpp>
#include <model/commands/assign_master_key.hpp>
#include <model/commands/create_account.hpp>
#include <model/commands/create_asset.hpp>
#include <model/commands/create_domain.hpp>
#include <model/commands/remove_signatory.hpp>
#include <model/commands/set_permissions.hpp>
#include <model/commands/set_quorum.hpp>
#include <model/commands/transfer_asset.hpp>

namespace iroha{
namespace ametsuchi{

using namespace rapidjson;

class BlockSerializer{
 public:
  std::vector<uint8_t > serialize(model::Block block);
  nonstd::optional<model::Block> deserialize(const std::vector<uint8_t >& bytes);
 private:
  void serialize(PrettyWriter<StringBuffer>& writer, const model::Block& block);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::Signature& signature);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::Transaction& transaction);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::Command& command);

  void serialize(PrettyWriter<StringBuffer>& writer, const model::AddPeer& add_peer);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::AddAssetQuantity& add_asset_quantity);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::AddSignatory& add_signatory);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::AssignMasterKey& assign_master_key);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::CreateAccount& create_account);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::CreateAsset& create_asset);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::CreateDomain& create_domain);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::RemoveSignatory& remove_signatory);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::SetAccountPermissions& set_account_permissions);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::SetQuorum& set_quorum);
  void serialize(PrettyWriter<StringBuffer>& writer, const model::TransferAsset& transfer_asset);

  void deserialize(Document& doc, std::vector<model::Transaction>& transactions);
  void deserialize(GenericValue<rapidjson::UTF8<char>>::Object& json_tx,
                   std::vector<std::shared_ptr<model::Command>>& commands);
  nonstd::optional<model::AddPeer> deserialize_add_peer(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::AddAssetQuantity> deserialize_add_asset_quantity(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::AddSignatory> deserialize_add_signatory(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::AssignMasterKey> deserialize_assign_master_key(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::CreateAccount> deserialize_create_account(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::CreateAsset> deserialize_create_asset(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::CreateDomain> deserialize_create_domain(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::RemoveSignatory> deserialize_remove_signatory(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::SetAccountPermissions> deserialize_set_account_permissions(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::SetQuorum> deserialize_set_quorum(GenericValue<UTF8<char>>::Object& json_command);
  nonstd::optional<model::TransferAsset> deserialize_transfer_asset(GenericValue<UTF8<char>>::Object& json_command);

  template<typename Base, typename T>
  inline bool instanceof(const T *ptr) {
    return typeid(Base) == typeid(*ptr);
  }
};

}
}

#endif //IROHA_BLOCK_SERIALIZER_HPP
