/* Copyright 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_SYNC_SETTINGS_H_
#define BRAVE_COMPONENTS_BRAVE_SYNC_SETTINGS_H_

#include <string>

namespace brave_sync {

class Settings {
 public:
  Settings();
  std::string this_device_name_;
  std::string this_device_id_;
  std::string this_device_id_v2_;
  bool sync_this_device_;
  bool sync_bookmarks_;
  bool sync_settings_;
  bool sync_history_;

  // sync_configured_ may be true, but sync_this_device_==false
  // So sync is suspended
  bool sync_configured_;
};

}  // namespace brave_sync

#endif  // BRAVE_COMPONENTS_BRAVE_SYNC_SETTINGS_H_
