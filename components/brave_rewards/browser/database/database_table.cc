/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/strings/stringprintf.h"
#include "brave/components/brave_rewards/browser/database/database_table.h"

namespace brave_rewards {

DatabaseTable::DatabaseTable(int current_db_version) {
  current_db_version_ = current_db_version;
}

DatabaseTable::~DatabaseTable() {
}

bool DatabaseTable::InsertIndex(
    sql::Database* db,
    const std::string& table_name,
    const std::string& key) {
  const std::string query = base::StringPrintf(
      "CREATE INDEX %s_%s_index ON %s (%s)",
      table_name.c_str(),
      key.c_str(),
      table_name.c_str(),
      key.c_str());

  return db->Execute(query.c_str());
}

int DatabaseTable::GetCurrentDBVersion() {
  return current_db_version_;
}

}  // namespace brave_rewards
