/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_CONTENT_SETTINGS_H_
#define BRAVE_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_CONTENT_SETTINGS_H_

#define BRAVE_CONTENT_SETTINGS_H                  \
  ContentSettingsForOneType autoplay_rules;       \
  ContentSettingsForOneType fingerprinting_rules; \
  ContentSettingsForOneType brave_shields_rules;

#include "../../../../../../components/content_settings/core/common/content_settings.h"

#undef BRAVE_CONTENT_SETTINGS_H

#endif  // BRAVE_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_CONTENT_SETTINGS_H_
