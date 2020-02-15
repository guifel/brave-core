// Copyright (c) 2019 The Brave Authors
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/webui/navigation_bar_data_provider.h"
#include "brave/grit/brave_generated_resources.h"
#include "content/public/browser/web_ui_data_source.h"

#define BRAVE_CREATE_BOOKMARKS_UI_HTML_SOURCE \
  NavigationBarDataProvider::Initialize(source); \
  source->AddLocalizedString( \
      "emptyList", IDS_BRAVE_BOOKMARK_MANAGER_EMPTY_LIST);

#include "../../../../../../chrome/browser/ui/webui/bookmarks/bookmarks_ui.cc"  // NOLINT

#undef BRAVE_CREATE_BOOKMARKS_UI_HTML_SOURCE
