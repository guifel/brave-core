/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_BROWSER_DATABASE_DATABASE_SERVER_PUBLISHER_BANNER_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_BROWSER_DATABASE_DATABASE_SERVER_PUBLISHER_BANNER_H_

#include <memory>
#include <string>

#include "bat/ledger/mojom_structs.h"
#include "brave/components/brave_rewards/browser/database/database_server_publisher_amounts.h"
#include "brave/components/brave_rewards/browser/database/database_server_publisher_links.h"
#include "brave/components/brave_rewards/browser/database/database_table.h"

namespace brave_rewards {

class DatabaseServerPublisherBanner: public DatabaseTable {
 public:
  explicit DatabaseServerPublisherBanner(int current_db_version);
  ~DatabaseServerPublisherBanner() override;

  bool Migrate(sql::Database* db, const int target) override;

  bool InsertOrUpdate(sql::Database* db, ledger::ServerPublisherInfoPtr info);

  ledger::PublisherBannerPtr GetRecord(
      sql::Database* db,
      const std::string& publisher_key);

 private:
  bool CreateTableV7(sql::Database* db);

  bool CreateTableV15(sql::Database* db);

  bool CreateIndexV7(sql::Database* db);

  bool CreateIndexV15(sql::Database* db);

  bool MigrateToV7(sql::Database* db);

  bool MigrateToV15(sql::Database* db);

  std::unique_ptr<DatabaseServerPublisherLinks> links_;
  std::unique_ptr<DatabaseServerPublisherAmounts> amounts_;
};

}  // namespace brave_rewards

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_BROWSER_DATABASE_DATABASE_SERVER_PUBLISHER_BANNER_H_
