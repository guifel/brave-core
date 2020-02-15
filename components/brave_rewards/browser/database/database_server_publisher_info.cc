/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <utility>

#include "base/bind.h"
#include "base/strings/stringprintf.h"
#include "brave/components/brave_rewards/browser/database/database_server_publisher_info.h"
#include "brave/components/brave_rewards/browser/database/database_util.h"
#include "sql/statement.h"
#include "sql/transaction.h"

namespace {
  const char table_name_[] = "server_publisher_info";
}  // namespace

namespace brave_rewards {

DatabaseServerPublisherInfo::DatabaseServerPublisherInfo(
    int current_db_version) :
    DatabaseTable(current_db_version),
    banner_(
        std::make_unique<DatabaseServerPublisherBanner>(current_db_version)) {
}

DatabaseServerPublisherInfo::~DatabaseServerPublisherInfo() {
}

bool DatabaseServerPublisherInfo::CreateTableV7(sql::Database* db) {
  const std::string query = base::StringPrintf(
      "CREATE TABLE %s "
      "("
      "publisher_key LONGVARCHAR PRIMARY KEY NOT NULL UNIQUE,"
      "status INTEGER DEFAULT 0 NOT NULL,"
      "excluded INTEGER DEFAULT 0 NOT NULL,"
      "address TEXT NOT NULL"
      ")",
      table_name_);

  return db->Execute(query.c_str());
}

bool DatabaseServerPublisherInfo::CreateIndexV7(sql::Database* db) {
  return this->InsertIndex(db, table_name_, "publisher_key");
}

bool DatabaseServerPublisherInfo::Migrate(
    sql::Database* db,
    const int target) {
  switch (target) {
    case 7: {
      return MigrateToV7(db);
    }
    case 15: {
      return MigrateToV15(db);
    }
    default: {
      NOTREACHED();
      return false;
    }
  }
}

bool DatabaseServerPublisherInfo::MigrateToV7(sql::Database* db) {
  if (db->DoesTableExist(table_name_)) {
    DropTable(db, table_name_);
  }

  if (!CreateTableV7(db)) {
    return false;
  }

  if (!CreateIndexV7(db)) {
    return false;
  }

  if (!banner_->Migrate(db, 7)) {
    return false;
  }

  return true;
}

bool DatabaseServerPublisherInfo::MigrateToV15(sql::Database* db) {
  return banner_->Migrate(db, 15);
}

bool DatabaseServerPublisherInfo::InsertOrUpdate(
    sql::Database* db,
    ledger::ServerPublisherInfoPtr info) {
  if (!info) {
    return false;
  }

  const std::string query = base::StringPrintf(
      "INSERT OR REPLACE INTO %s "
      "(publisher_key, status, excluded, address) "
      "VALUES (?, ?, ?, ?)",
      table_name_);

  sql::Statement statment(
    db->GetCachedStatement(SQL_FROM_HERE, query.c_str()));

  statment.BindString(0, info->publisher_key);
  statment.BindInt(1, static_cast<int>(info->status));
  statment.BindBool(2, info->excluded);
  statment.BindString(3, info->address);

  return statment.Run();
}

bool DatabaseServerPublisherInfo::ClearAndInsertList(
    sql::Database* db,
    const ledger::ServerPublisherInfoList& list) {
  const std::string clear_query = base::StringPrintf(
      "DELETE FROM %s",
      table_name_);

  bool success = db->Execute(clear_query.c_str());
  if (!success) {
    return false;
  }

  if (list.size() == 0) {
    return true;
  }

  sql::Transaction transaction(db);
  if (!transaction.Begin()) {
    return false;
  }

  for (const auto& info : list) {
    if (!info) {
      continue;
    }

    if (!InsertOrUpdate(db, info->Clone())) {
      transaction.Rollback();
      return false;
    }

    if (info->banner) {
      if (!banner_->InsertOrUpdate(db, info->Clone())) {
        transaction.Rollback();
        return false;
      }
    }
  }

  return transaction.Commit();
}

ledger::ServerPublisherInfoPtr DatabaseServerPublisherInfo::GetRecord(
    sql::Database* db,
    const std::string& publisher_key) {
  const std::string query = base::StringPrintf(
      "SELECT status, excluded, address "
      "FROM %s "
      "WHERE publisher_key=?",
      table_name_);

  sql::Statement statment(db->GetUniqueStatement(query.c_str()));
  statment.BindString(0, publisher_key);

  if (!statment.Step()) {
    return nullptr;
  }

  auto info = ledger::ServerPublisherInfo::New();
  info->publisher_key = publisher_key;
  info->status =
      static_cast<ledger::mojom::PublisherStatus>(statment.ColumnInt(0));
  info->excluded = statment.ColumnBool(1);
  info->address = statment.ColumnString(2);
  info->banner = banner_->GetRecord(db, publisher_key);

  return info;
}

}  // namespace brave_rewards
