/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/tabs/brave_tab_strip_model.h"

#include "ui/events/event.h"
#include "ui/events/event_handler.h"
#include "chrome/browser/profiles/profile.h" // Needed for getting perf
#include "components/prefs/pref_service.h" // Needed for getting perf
#include "content/public/browser/web_contents.h" // Needed for getting pref
#include "brave/common/pref_names.h" // Same

#if defined(USE_AURA)
#include "ui/aura/window.h"
#endif


BraveTabStripModel::BraveTabStripModel(TabStripModelDelegate* delegate, Profile* profile)
	: TabStripModel(delegate, profile) {
    LOG(WARNING) << "=== BraveTabStripModel ==="
  }

BraveTabStripModel::~BraveTabStripModel() {}

void BraveTabStripModel::SelectNextTab(UserGestureDetails detail) {
  bool isMRUEnabled = Profile::FromBrowserContext(GetActiveWebContents()->GetBrowserContext())->GetPrefs()->GetBoolean(kMRUCyclingEnabled);
  if(isMRUEnabled) {
     SelectTabMRU(false, detail);
  } else {
     SelectRelativeTab(true, detail);
  }
}

void BraveTabStripModel::SelectPreviousTab(UserGestureDetails detail) {
  bool isMRUEnabled = Profile::FromBrowserContext(GetActiveWebContents()->GetBrowserContext())->GetPrefs()->GetBoolean(kMRUCyclingEnabled);

  if(isMRUEnabled) {
     SelectTabMRU(true, detail);
  } else {
     SelectRelativeTab(false, detail);
  }
}

void BraveTabStripModel::SelectTabMRU(bool backward, UserGestureDetails detail) {
  if(current_mru_cycling_index == -1) {
      // Start cycling

      // Create a list of tab indexes sorted by time of last activation
      for (int i = 0; i < count(); ++i) {
        mru_cycle_list.push_back(i);
      }

      std::sort(mru_cycle_list.begin(), mru_cycle_list.end(), [this](int a, int b){
        return GetWebContentsAt(a)->GetLastActiveTime() >
          GetWebContentsAt(b)->GetLastActiveTime();
      });

      // Create an event handler eating all keyboard events while tabing
      ctrl_released_event_handler = std::make_unique<CtrlReleaseHandler>(this);

      // TODO: I am really not sure that this will work for MACOS
      gfx::NativeView root = this->GetActiveWebContents()->GetNativeView();
      while (root && root->parent()){
        root = root->parent();
      }

      root->AddPreTargetHandler(ctrl_released_event_handler.get());

      current_mru_cycling_index = 0;
  }

  int tabCount = count();

  if(backward) {
    current_mru_cycling_index = (current_mru_cycling_index - 1 % tabCount + tabCount) % tabCount;
  } else {
    current_mru_cycling_index = (current_mru_cycling_index + 1 % tabCount + tabCount) % tabCount;
  }

  LOG(WARNING) << "Go to tab: " << mru_cycle_list[current_mru_cycling_index] << "current_mru_cycling_index:" << current_mru_cycling_index;

  ActivateTabAt(mru_cycle_list[current_mru_cycling_index], detail);
}

void BraveTabStripModel::StopMRUCycling() {
  current_mru_cycling_index = -1;
  mru_cycle_list.clear();

  if(ctrl_released_event_handler) {

    gfx::NativeView root = this->GetActiveWebContents()->GetNativeView();
    while (root && root->parent()){
      root = root->parent();
    }
    root->RemovePreTargetHandler(ctrl_released_event_handler.get());
    ctrl_released_event_handler.reset();
  }

}


BraveTabStripModel::CtrlReleaseHandler::CtrlReleaseHandler(BraveTabStripModel* tab_strip): tab_strip(tab_strip) {
  LOG(WARNING) << "Ctrl handler created";
}

BraveTabStripModel::CtrlReleaseHandler::~CtrlReleaseHandler() {
  LOG(WARNING) << "Ctrl handler Destroyed";
}

void BraveTabStripModel::CtrlReleaseHandler::OnKeyEvent(ui::KeyEvent* event) {
  if (event->key_code() == ui::VKEY_CONTROL && event->type() == ui::ET_KEY_RELEASED) {
    LOG(WARNING) << "Stop cycling CTRL RELEASED";
    tab_strip->StopMRUCycling();
    return;
  } else if (event->key_code() == ui::VKEY_TAB  && event->type() == ui::ET_KEY_PRESSED) {
    // Block all keys except tab down while cycling
    return;
  }
    LOG(WARNING) << "BLOCK KEY: " << event->key_code() << " Type: " << event->type();
    event->StopPropagation();
}