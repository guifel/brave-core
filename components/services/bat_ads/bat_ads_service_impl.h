/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_SERVICES_BAT_ADS_BAT_ADS_SERVICE_IMPL_H_
#define BRAVE_COMPONENTS_SERVICES_BAT_ADS_BAT_ADS_SERVICE_IMPL_H_

#include <string>
#include <memory>

#include "base/memory/ref_counted.h"
#include "bat/ads/ads.h"
#include "brave/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"
#include "mojo/public/cpp/bindings/unique_associated_receiver_set.h"
#include "services/service_manager/public/cpp/service_context_ref.h"

namespace bat_ads {

class BatAdsServiceImpl : public mojom::BatAdsService {
 public:
  explicit BatAdsServiceImpl(
      std::unique_ptr<service_manager::ServiceContextRef> service_ref);

  ~BatAdsServiceImpl() override;

  // Overridden from BatAdsService:
  void Create(
      mojo::PendingAssociatedRemote<mojom::BatAdsClient> client_info,
      mojo::PendingAssociatedReceiver<mojom::BatAds> bat_ads,
      CreateCallback callback) override;

  void SetEnvironment(
      const ads::Environment environment,
      SetEnvironmentCallback callback) override;

  void SetTesting(
      const bool is_testing,
      SetTestingCallback callback) override;

  void SetDebug(
      const bool is_debug,
      SetDebugCallback callback) override;

 private:
  const std::unique_ptr<service_manager::ServiceContextRef> service_ref_;
  bool is_initialized_;
  mojo::UniqueAssociatedReceiverSet<mojom::BatAds> receivers_;

  DISALLOW_COPY_AND_ASSIGN(BatAdsServiceImpl);
};

}  // namespace bat_ads

#endif  // BRAVE_COMPONENTS_SERVICES_BAT_ADS_BAT_ADS_SERVICE_IMPL_H_
