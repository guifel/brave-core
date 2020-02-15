/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/services/bat_ads/bat_ads_app.h"

#include <string>
#include <utility>

#include "brave/components/services/bat_ads/bat_ads_service_impl.h"

namespace bat_ads {

void BatAdsApp::BindBatAdsServiceReceiver(
    service_manager::ServiceKeepalive* keepalive,
    mojo::PendingReceiver<bat_ads::mojom::BatAdsService> receiver) {
  receivers_.Add(
      std::make_unique<bat_ads::BatAdsServiceImpl>(keepalive->CreateRef()),
      std::move(receiver));
}

BatAdsApp::BatAdsApp(service_manager::mojom::ServiceRequest request) :
    service_binding_(this, std::move(request)),
    service_keepalive_(&service_binding_, base::TimeDelta()) {
}

BatAdsApp::~BatAdsApp() {}

void BatAdsApp::OnStart() {
  binders_.Add(base::BindRepeating(&BatAdsApp::BindBatAdsServiceReceiver,
                                   base::Unretained(this),
                                   &service_keepalive_));
}

void BatAdsApp::OnConnect(
    const service_manager::ConnectSourceInfo& source_info,
    const std::string& interface_name,
    mojo::ScopedMessagePipeHandle receiver_pipe) {
  binders_.TryBind(interface_name, &receiver_pipe);
}

}  // namespace bat_ads
