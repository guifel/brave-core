/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string>

#include "base/files/file_path.h"
#include "brave/common/pref_names.h"
#include "brave/components/ntp_sponsored_images/browser/ntp_sponsored_images_data.h"
#include "brave/components/ntp_sponsored_images/browser/ntp_sponsored_images_service.h"
#include "brave/components/ntp_sponsored_images/browser/view_counter_service.h"
#include "brave/components/ntp_sponsored_images/common/pref_names.h"
#include "components/prefs/testing_pref_service.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"

using ntp_sponsored_images::ViewCounterService;
using ntp_sponsored_images::NTPSponsoredImagesData;
using ntp_sponsored_images::NTPSponsoredImagesService;


class NTPSponsoredImagesViewCounterTest : public testing::Test {
 public:
  NTPSponsoredImagesViewCounterTest() = default;
  ~NTPSponsoredImagesViewCounterTest() override = default;

  void SetUp() override {
    // Need ntp_sponsored_images prefs
    auto* registry = prefs()->registry();
    ViewCounterService::RegisterProfilePrefs(registry);
    // Need general prefs for "ShowBackgroundImage"
    registry->RegisterBooleanPref(kNewTabPageShowBackgroundImage, true);

    service_ = std::make_unique<NTPSponsoredImagesService>(nullptr);
    view_counter_ = std::make_unique<ViewCounterService>(
        service_.get(), prefs(), true);
  }

  void OptOut() {
    prefs()->SetBoolean(
        ntp_sponsored_images::prefs::kNewTabPageShowBrandedBackgroundImage,
        false);
  }

  void OptIn() {
    prefs()->SetBoolean(
        ntp_sponsored_images::prefs::kNewTabPageShowBrandedBackgroundImage,
        true);
  }

  std::unique_ptr<NTPSponsoredImagesData> CreateGoodData() {
    auto data = std::make_unique<NTPSponsoredImagesData>();
    data->url_prefix = "not://real/data/";
    data->wallpaper_image_files = {
        base::FilePath(FILE_PATH_LITERAL("fake1.jpg")),
        base::FilePath(FILE_PATH_LITERAL("fake2.jpg")),
    };
    data->logo_alt_text = "Test alt text.";
    data->logo_company_name = "Test";
    data->logo_destination_url = "not://real.site";
    return data;
  }

  sync_preferences::TestingPrefServiceSyncable* prefs() { return &prefs_; }

 protected:
  sync_preferences::TestingPrefServiceSyncable prefs_;
  std::unique_ptr<ViewCounterService> view_counter_;
  std::unique_ptr<NTPSponsoredImagesService> service_;
};

TEST_F(NTPSponsoredImagesViewCounterTest, NotActiveInitially) {
  // By default, data is bad and wallpaper is not active.
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());
}

TEST_F(NTPSponsoredImagesViewCounterTest, NotActiveWithBadData) {
  // Set some bad data explicitly.
  NTPSponsoredImagesData* badData = new NTPSponsoredImagesData;
  service_->images_data_.reset(badData);
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());
}

TEST_F(NTPSponsoredImagesViewCounterTest, NotActiveOptedOut) {
  // Even with good data, wallpaper should not be active if user pref is off.
  service_->images_data_ = CreateGoodData();
  OptOut();
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());
}

TEST_F(NTPSponsoredImagesViewCounterTest, IsActiveOptedIn) {
  service_->images_data_ = CreateGoodData();
  OptIn();
  EXPECT_TRUE(view_counter_->IsBrandedWallpaperActive());
}

TEST_F(NTPSponsoredImagesViewCounterTest, ActiveInitiallyOptedIn) {
  // Sanity check that the default is still to be opted-in.
  // If this gets manually changed, then this test should be manually changed
  // too.
  service_->images_data_ = CreateGoodData();
  EXPECT_TRUE(view_counter_->IsBrandedWallpaperActive());
}

