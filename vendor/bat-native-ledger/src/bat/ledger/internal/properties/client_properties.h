/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_PROPERTIES_CLIENT_PROPERTIES_H_
#define BRAVELEDGER_PROPERTIES_CLIENT_PROPERTIES_H_

#include <stdint.h>
#include <map>
#include <string>

#include "bat/ledger/internal/properties/ballot_properties.h"
#include "bat/ledger/internal/properties/publisher_votes_properties.h"
#include "bat/ledger/internal/properties/current_reconcile_properties.h"
#include "bat/ledger/internal/properties/transaction_properties.h"
#include "bat/ledger/internal/properties/wallet_info_properties.h"
#include "bat/ledger/mojom_structs.h"

namespace ledger {

struct ClientProperties {
  ClientProperties();
  ClientProperties(
      const ClientProperties& properties);
  ~ClientProperties();

  bool operator==(
      const ClientProperties& rhs) const;

  bool operator!=(
      const ClientProperties& rhs) const;

  WalletInfoProperties wallet_info;
  WalletProperties wallet;
  uint64_t boot_timestamp;
  uint64_t reconcile_timestamp;
  std::string persona_id;
  std::string user_id;
  std::string registrar_vk;
  std::string master_user_token;
  std::string pre_flight;
  std::string fee_currency;
  std::string settings;
  double fee_amount;
  bool user_changed_fee;
  uint32_t days;
  Transactions transactions;
  Ballots ballots;
  PublisherVotes publisher_votes;
  CurrentReconciles current_reconciles;
  bool auto_contribute;
  bool rewards_enabled;
  std::map<std::string, bool> inline_tips;
};

}  // namespace ledger

#endif  // BRAVELEDGER_PROPERTIES_CLIENT_PROPERTIES_H_
