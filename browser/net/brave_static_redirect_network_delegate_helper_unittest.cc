/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/net/brave_static_redirect_network_delegate_helper.h"

#include <memory>
#include <string>

#include "brave/browser/net/url_context.h"
#include "brave/browser/translate/buildflags/buildflags.h"
#include "brave/common/network_constants.h"
#include "brave/common/translate_network_constants.h"
#include "components/component_updater/component_updater_url_constants.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"
#include "url/url_constants.h"

using brave::ResponseCallback;

TEST(BraveStaticRedirectNetworkDelegateHelperTest, NoModifyTypicalURL) {
  const GURL url("https://bradhatesprimes.brave.com/composite_numbers_ftw");
  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_TRUE(request_info->new_url_spec.empty());
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyGeoURL) {
  const GURL url(
      "https://www.googleapis.com/geolocation/v1/geolocate?key=2_3_5_7");
  const GURL expected_url(GOOGLEAPIS_ENDPOINT GOOGLEAPIS_API_KEY);

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyCRLSet1) {
  const GURL url(
      "https://dl.google.com/release2/chrome_component/AJ4r388iQSJq_4819/"
      "4819_all_crl-set-5934829738003798040.data.crx3");
  const GURL expected_url(
      "https://crlsets.brave.com/release2/chrome_component/"
      "AJ4r388iQSJq_4819/4819_all_crl-set-5934829738003798040.data.crx3");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyCRLSet2) {
  const GURL url(
      "https://r2---sn-8xgp1vo-qxoe.gvt1.com/edgedl/release2/"
      "chrome_component/AJ4r388iQSJq_4819/4819_all_crl-set-5934829738003798040"
      ".data.crx3");
  const GURL expected_url(
      "https://crlsets.brave.com/edgedl/release2/chrome_compone"
      "nt/AJ4r388iQSJq_4819/4819_all_crl-set-5934829738003798040.data.crx3");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyCRLSet3) {
  const GURL url(
      "https://www.google.com/dl/release2/chrome_component/LLjIBPPmveI_4988/"
      "4988_all_crl-set-6296993568184466307.data.crx3");
  const GURL expected_url(
      "https://crlsets.brave.com/dl/release2/chrome_component/LLjIBPPmveI_4988/"
      "4988_all_crl-set-6296993568184466307.data.crx3");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyCRXDownload) {
  const GURL url(
      "https://clients2.googleusercontent.com/crx/blobs/QgAAAC6zw0qH2DJtn"
      "Xe8Z7rUJP1RM6lX7kVcwkQ56ujmG3AWYOAkxoNnIdnEBUz_"
      "3z4keVhjzzAF10srsaL7lrntfB"
      "IflcYIrTziwX3SUS9i_P-CAMZSmuV5tdQl-Roo6cnVC_GRzKsnZSKm1Q/"
      "extension_2_0_67"
      "3_0.crx");
  const GURL expected_url(
      "https://crxdownload.brave.com/crx/blobs/QgAAAC6"
      "zw0qH2DJtnXe8Z7rUJP1RM6lX7kVcwkQ56ujmG3AWYOAkxoNnIdnEBUz_"
      "3z4keVhjzzAF10sr"
      "saL7lrntfBIflcYIrTziwX3SUS9i_P-CAMZSmuV5tdQl-Roo6cnVC_GRzKsnZSKm1Q/"
      "extens"
      "ion_2_0_673_0.crx");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyCRLSet1_http) {
  const GURL url(
      "http://dl.google.com/release2/chrome_component/AJ4r388iQSJq_4819/"
      "4819_all_crl-set-5934829738003798040.data.crx3");
  const GURL expected_url(
      "https://crlsets.brave.com/release2/chrome_component/"
      "AJ4r388iQSJq_4819/4819_all_crl-set-5934829738003798040.data.crx3");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyCRLSet2_http) {
  const GURL url(
      "http://r2---sn-8xgp1vo-qxoe.gvt1.com/edgedl/release2/"
      "chrome_component/AJ4r388iQSJq_4819/4819_all_crl-set-5934829738003798040"
      ".data.crx3");
  const GURL expected_url(
      "https://crlsets.brave.com/edgedl/release2/chrome_compone"
      "nt/AJ4r388iQSJq_4819/4819_all_crl-set-5934829738003798040.data.crx3");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyCRLSet3_http) {
  const GURL url(
      "http://www.google.com/dl/release2/chrome_component/LLjIBPPmveI_4988/"
      "4988_all_crl-set-6296993568184466307.data.crx3");
  const GURL expected_url(
      "https://crlsets.brave.com/dl/release2/chrome_component/LLjIBPPmveI_4988/"
      "4988_all_crl-set-6296993568184466307.data.crx3");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyCRXDownload_http) {
  const GURL url(
      "http://clients2.googleusercontent.com/crx/blobs/QgAAAC6zw0qH2DJtn"
      "Xe8Z7rUJP1RM6lX7kVcwkQ56ujmG3AWYOAkxoNnIdnEBUz_"
      "3z4keVhjzzAF10srsaL7lrntfB"
      "IflcYIrTziwX3SUS9i_P-CAMZSmuV5tdQl-Roo6cnVC_GRzKsnZSKm1Q/"
      "extension_2_0_67"
      "3_0.crx");
  const GURL expected_url(
      "https://crxdownload.brave.com/crx/blobs/QgAAAC6"
      "zw0qH2DJtnXe8Z7rUJP1RM6lX7kVcwkQ56ujmG3AWYOAkxoNnIdnEBUz_"
      "3z4keVhjzzAF10sr"
      "saL7lrntfBIflcYIrTziwX3SUS9i_P-CAMZSmuV5tdQl-Roo6cnVC_GRzKsnZSKm1Q/"
      "extens"
      "ion_2_0_673_0.crx");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifySafeBrowsingURLV4) {
  const GURL url(
      "https://safebrowsing.googleapis.com/v4/"
      "threatListUpdates:fetch?$req=ChkKCGNocm9taXVtEg02Ni");
  GURL::Replacements replacements;
  replacements.SetHostStr(SAFEBROWSING_ENDPOINT);
  const GURL expected_url(url.ReplaceComponents(replacements));

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifySafeBrowsingURLV5) {
  const GURL url(
      "https://safebrowsing.googleapis.com/v5/"
      "threatListUpdates:fetch?$req=ChkKCGNocm9taXVtEg02Ni");
  GURL::Replacements replacements;
  replacements.SetHostStr(SAFEBROWSING_ENDPOINT);
  GURL expected_url(url.ReplaceComponents(replacements));

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyGvt1) {
  const GURL url(
      "http://redirector.gvt1.com/edgedl/release2/"
      "NfaZYtcKdtFc0LUvFkcNFA_0.3/AKveSIjhHAm2K09XAMovFEQ");
  const GURL expected_url(
      "https://redirector.brave.com/edgedl/release2/"
      "NfaZYtcKdtFc0LUvFkcNFA_0.3/AKveSIjhHAm2K09XAMovFEQ");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, ModifyGoogleDl) {
  const GURL url(
      "http://dl.google.com/release2/"
      "NfaZYtcKdtFc0LUvFkcNFA_0.3/AKveSIjhHAm2K09XAMovFEQ");
  const GURL expected_url(
      "https://redirector.brave.com/release2/"
      "NfaZYtcKdtFc0LUvFkcNFA_0.3/AKveSIjhHAm2K09XAMovFEQ");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

// TODO(@fmarier): Re-enable download protection once we have
// truncated the list of metadata that it sends to the server
// (brave/brave-browser#6267).
#if 0
TEST(BraveStaticRedirectNetworkDelegateHelperTest,
     ModifySafeBrowsingFileCheckURL) {
  const GURL url(
      "https://sb-ssl.google.com/safebrowsing/clientreport/download?"
      "key=DUMMY_KEY");
  GURL expected_url(
      "https://sb-ssl.brave.com/safebrowsing/clientreport/download?"
      "key=DUMMY_KEY");

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}
#endif  // 0

#if BUILDFLAG(ENABLE_BRAVE_TRANSLATE_GO)
TEST(BraveStaticRedirectNetworkDelegateHelperTest, RedirectTranslate) {
  const std::string query_string(
      "?cb=cr.googleTranslate.onTranslateElementLoad&aus=true&"
      "clc=cr.googleTranslate.onLoadCSS&"
      "jlc=cr.googleTranslate.onLoadJavascript&hl=en&key=DUMMY_KEY");
  const std::string path_string("/translate_a/element.js");
  const std::string google_host_string("https://translate.googleapis.com");
  const GURL url(google_host_string + path_string + query_string);
  const GURL expected_url(kBraveTranslateServer + path_string + query_string);

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveStaticRedirectNetworkDelegateHelperTest, RedirectTranslateLanguage) {
  const GURL url(
      "https://translate.googleapis.com/translate_a/l?"
      "client=chrome&hl=en&key=DUMMY_KEY");
  const GURL expected_url(kBraveTranslateLanguageEndpoint);

  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_StaticRedirectWork(ResponseCallback(), request_info);
  EXPECT_EQ(request_info->new_url_spec, expected_url);
  EXPECT_EQ(rc, net::OK);
}
#endif
