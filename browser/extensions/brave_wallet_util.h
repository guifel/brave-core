/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_EXTENSIONS_BRAVE_WALLET_UTIL_H_
#define BRAVE_BROWSER_EXTENSIONS_BRAVE_WALLET_UTIL_H_

#include <string>

namespace extensions {

std::string GetInfuraProjectID();

bool HasInfuraProjectID();

}  // namespace extensions

#endif  // BRAVE_BROWSER_EXTENSIONS_BRAVE_WALLET_UTIL_H_
