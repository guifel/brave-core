/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_ADS_HISTORY_DATE_RANGE_FILTER_H_
#define BAT_ADS_INTERNAL_ADS_HISTORY_DATE_RANGE_FILTER_H_

#include <stdint.h>
#include <deque>

#include "bat/ads/ad_history.h"

namespace ads {

struct AdsHistory;

class AdsHistoryDateRangeFilter {
 public :
  AdsHistoryDateRangeFilter();
  ~AdsHistoryDateRangeFilter();

  std::deque<AdHistory> Apply(
      const std::deque<AdHistory>& history,
      const uint64_t from_timestamp,
      const uint64_t to_timestamp) const;
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_ADS_HISTORY_DATE_RANGE_FILTER_H_
