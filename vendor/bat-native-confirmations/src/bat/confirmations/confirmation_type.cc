/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/confirmations/confirmation_type.h"

namespace confirmations {

const char kConfirmationTypeClick[] = "click";
const char kConfirmationTypeDismiss[] = "dismiss";
const char kConfirmationTypeView[] = "view";
const char kConfirmationTypeLanded[] = "landed";
const char kConfirmationTypeFlag[] = "flag";
const char kConfirmationTypeUpvote[] = "upvote";
const char kConfirmationTypeDownvote[] = "downvote";
const char kConfirmationTypeConversion[] = "conversion";

ConfirmationType::ConfirmationType(
    const std::string& value) {
  if (value == kConfirmationTypeClick) {
    value_ = CLICK;
  } else if (value == kConfirmationTypeDismiss) {
    value_ = DISMISS;
  } else if (value == kConfirmationTypeView) {
    value_ = VIEW;
  } else if (value == kConfirmationTypeLanded) {
    value_ = LANDED;
  } else if (value == kConfirmationTypeFlag) {
    value_ = FLAG;
  } else if (value == kConfirmationTypeUpvote) {
    value_ = UPVOTE;
  } else if (value == kConfirmationTypeDownvote) {
    value_ = DOWNVOTE;
  } else if (value == kConfirmationTypeConversion) {
    value_ = CONVERSION;
  } else {
    value_ = UNKNOWN;
  }
}

bool ConfirmationType::IsSupported() const {
  return value_ != UNKNOWN;
}

ConfirmationType::Value ConfirmationType::value() const {
  return value_;
}

ConfirmationType::operator std::string() const {
  switch (value_) {
    case CLICK: {
      return kConfirmationTypeClick;
    }

    case DISMISS: {
      return kConfirmationTypeDismiss;
    }

    case VIEW: {
      return kConfirmationTypeView;
    }

    case LANDED: {
      return kConfirmationTypeLanded;
    }

    case FLAG: {
      return kConfirmationTypeFlag;
    }

    case UPVOTE: {
      return kConfirmationTypeUpvote;
    }

    case DOWNVOTE: {
      return kConfirmationTypeDownvote;
    }

    case CONVERSION: {
      return kConfirmationTypeConversion;
    }

    case UNKNOWN: {
      return "";
    }
  }
}

bool ConfirmationType::operator==(
    ConfirmationType type) const {
  return value_ == type.value_;
}

bool ConfirmationType::operator!=(
    ConfirmationType type) const {
  return value_ != type.value_;
}

}  // namespace confirmations
