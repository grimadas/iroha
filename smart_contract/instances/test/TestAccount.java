/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.
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

package instances.test;

import repository.Repository;
import java.util.HashMap;

import static repository.KeyConstants.*;

public class TestAccount {

  private static Repository repository = new Repository();

  public static void printSuccess() {
    System.out.println("==============================================");
    System.out.println("Success");
    System.out.println("==============================================");
  }

  public static void printFail(IllegalStateException e) {
    System.err.println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    System.err.println("Fail");
    System.err.println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    System.err.println(e.getMessage() + " in " + e.getClass().getName());
  }

  public static void testAddAccount(HashMap<String, String> params, String[] assets) throws IllegalStateException {
    try {
      // *******************************************************
      // Sorry... Interface is big chaned
      // *******************************************************
      /*
      // Print received params
      System.out.println("----------------------------------------------");
      System.out.println("Params pubKey:      " + params.get(PublicKey));
      System.out.println("Params accountName: " + params.get(AccountName));
      for (int i = 0; i < assets.length; i++) {
        System.out.println("Params assets[" + i + "]: " + assets[i]);
      }
      System.out.println("----------------------------------------------");

      // 1. Add account.
      System.out.println("Call accountRepo.add()");
      repository.accountAdd(
        params,
        assets
      );

      // 2. Find account data by PublicKey.
      System.out.println("Call repository.findByUuid()");
      HashMap<String, String> publicKeymap = new HashMap<String, String>();
      publicKeymap.put(PublicKey, params.get(PublicKey));
      HashMap<String, String> accountMap = repository.accountInfoFindByUuid(publicKeymap);
      String[] assetsArray = repository.accountValueFindByUuid(publicKeymap);

      System.out.println("----------------------------------------------");
      System.out.println("Received from C++: found pubKey:      " + accountMap.get(PublicKey));
      System.out.println("Received from C++: found accountName: " + accountMap.get(AccountName));
      for (int i = 0; i < assets.length; i++) {
        System.out.println("Received from C++: found assets[" + i + "]:   " + assetsArray[i]);
      }
      System.out.println("----------------------------------------------");

      // 3. Ensure the integrity.
      /*
      assert accountMap.get(PublicKey).equals(params.get(PublicKey));
      assert accountMap.get(AccountName).equals(params.get(AccountName));
      /
      if (!accountMap.get(PublicKey).equals(params.get(PublicKey)))
        throw new IllegalStateException("Mismatch public key");

      if (!accountMap.get(AccountName).equals(params.get(AccountName)))
        throw new IllegalStateException("Mismatch account name");

      printSuccess();
      */
      throw new IllegalStateException("Sorry unsupported");
    } catch(IllegalStateException e) {
      printFail(e);
    }
  }

  public static void testAttachAssetToAccount(HashMap<String, String> params) {
    try {
      // Print received params
      System.out.println("----------------------------------------------");
      System.out.println("Params uuid:              " + params.get(Uuid));
      System.out.println("Params attachedAssetUuid: " + params.get(AttachedAssetUuid));
      System.out.println("----------------------------------------------");

      // 1. Add account.
      System.out.println("Call accountRepo.add()");

      if (!repository.accountAttach(
        params
      )) throw new IllegalStateException("Cannot attach asset to account");

      System.out.println("----------------------------------------------");
      System.out.println("Received from C++: uuid: " + params.get(Uuid));
      System.out.println("----------------------------------------------");

      // 2. Find account data by uuid.
      System.out.println("Call repository.findByUuid()");
      HashMap<String, String> uuidmap = new HashMap<String, String>();
      uuidmap.put(Uuid, params.get(Uuid));
      HashMap<String, String> accountMap = repository.accountInfoFindByUuid(uuidmap);
      String[] assetsArray = repository.accountValueFindByUuid(uuidmap);

      System.out.println("----------------------------------------------");
      System.out.println("Received from C++: found pubKey:      " + accountMap.get(PublicKey));
      System.out.println("Received from C++: found accountName: " + accountMap.get(AccountName));
      for (int i = 0; i < assetsArray.length; i++) {
        System.out.println("Received from C++: found assets[" + i + "]:   " + assetsArray[i]);
      }
      System.out.println("----------------------------------------------");

      // 3. Ensure the integrity.
      if (assetsArray.length == 0)
        throw new IllegalStateException("assetsArray is empty.");
      if (!assetsArray[assetsArray.length - 1].equals(params.get(AttachedAssetUuid)))
        throw new IllegalStateException("Mismatch attachedAssetUuid");

      printSuccess();
    } catch(IllegalStateException e) {
      printFail(e);
    }
  }

  public static void testUpdateAccount(HashMap<String, String> params, String[] assets) throws IllegalStateException {
    try {
      // Print received params
      System.out.println("----------------------------------------------");
      System.out.println("Params accountName: " + params.get(AccountName));
      for (int i = 0; i < assets.length; i++) {
        System.out.println("Params assets[" + i + "]: " + assets[i]);
      }
      System.out.println("----------------------------------------------");

      // 1. Add account.
      System.out.println("Call accountRepo.add()");

      if (! repository.accountUpdate(
        params,
        assets
      )) throw new IllegalStateException("Cannot update account");

      System.out.println("----------------------------------------------");
      System.out.println("Received from C++: uuid: " + params.get(Uuid));
      System.out.println("----------------------------------------------");

      // 2. Find account data by uuid.
      System.out.println("Call accountRepo.findByUuid()");
      HashMap<String, String> accountMap = repository.accountInfoFindByUuid(params);
      String[] assetsArray = repository.accountValueFindByUuid(params);

      System.out.println("----------------------------------------------");
      System.out.println("Received from C++: found pubKey:      " + accountMap.get(PublicKey));
      System.out.println("Received from C++: found accountName: " + accountMap.get(AccountName));
      for (int i = 0; i < assets.length; i++) {
        System.out.println("Received from C++: found assets[" + i + "]:   " + assetsArray[i]);
      }
      System.out.println("----------------------------------------------");

      // 3. Ensure the integrity.

      if (!accountMap.get(AccountName).equals(params.get(AccountName)))
        throw new IllegalStateException("Mismatch account name");

      printSuccess();
    } catch(IllegalStateException e) {
      printFail(e);
    }
  }

  public static void testRemoveAccount(HashMap<String, String> params) throws IllegalStateException {
    try {
      // Print received params
      System.out.println("----------------------------------------------");
      System.out.println("Params uuid: " + params.get(Uuid));
      System.out.println("----------------------------------------------");

      if (!repository.accountRemove(params))
        throw new IllegalStateException("Cannot remove account");

      printSuccess();
    } catch(IllegalStateException e) {
      printFail(e);
    }
  }
}
