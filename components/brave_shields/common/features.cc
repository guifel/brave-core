// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "brave/components/brave_shields/common/features.h"

#include "base/feature_list.h"

namespace brave_shields {
namespace features {

const base::Feature kBraveAdblockCosmeticFiltering{
    "BraveAdblockCosmeticFiltering",
    base::FEATURE_DISABLED_BY_DEFAULT};

}  // namespace features
}  // namespace brave_shields
