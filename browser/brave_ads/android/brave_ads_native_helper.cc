/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "brave/browser/brave_ads/android/jni_headers/BraveAdsNativeHelper_jni.h"
#include "brave/components/brave_ads/browser/ads_service.h"
#include "brave/components/brave_ads/browser/ads_service_factory.h"
#include "brave/components/brave_ads/browser/locale_helper_android.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_android.h"

using base::android::JavaParamRef;
using base::android::ScopedJavaLocalRef;

namespace chrome {

namespace android {

// static

jboolean JNI_BraveAdsNativeHelper_IsBraveAdsEnabled(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile_android);
  auto* ads_service_ = brave_ads::AdsServiceFactory::GetForProfile(profile);
  if (!ads_service_) {
    return false;
  }

  return ads_service_->IsEnabled();
}

jboolean JNI_BraveAdsNativeHelper_IsLocaleValid(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile_android);
  auto* ads_service_ = brave_ads::AdsServiceFactory::GetForProfile(profile);
  if (!ads_service_) {
    return false;
  }

  return ads_service_->IsSupportedLocale();
}

void JNI_BraveAdsNativeHelper_SetAdsEnabled(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile_android);
  auto* ads_service_ = brave_ads::AdsServiceFactory::GetForProfile(profile);
  if (!ads_service_) {
    return;
  }

  ads_service_->SetEnabled(true);
}

base::android::ScopedJavaLocalRef<jstring>
  JNI_BraveAdsNativeHelper_GetCountryCode(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& jlocale) {

  std::string locale = base::android::ConvertJavaStringToUTF8(env, jlocale);
  std::string country_code =
    brave_ads::LocaleHelperAndroid::GetCountryCode(locale);
  return base::android::ConvertUTF8ToJavaString(env, country_code);
}

base::android::ScopedJavaLocalRef<jstring> JNI_BraveAdsNativeHelper_GetLocale(
  JNIEnv* env) {
  brave_ads::LocaleHelper* locale_helper =
    brave_ads::LocaleHelper::GetInstance();
  std::string locale = locale_helper->GetLocale();
  return base::android::ConvertUTF8ToJavaString(env, locale);
}

}  // namespace android

}  // namespace chrome
