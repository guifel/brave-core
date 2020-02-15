/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { render } from 'react-dom'
import { Provider } from 'react-redux'
import { initLocale } from 'brave-ui'
import { bindActionCreators } from 'redux'
require('emptykit.css')

// Components
import App from './components/app'
require('../../../../ui/webui/resources/fonts/muli.css')
require('../../../../ui/webui/resources/fonts/poppins.css')

// Utils
import store from './store'
import { ThemeProvider } from 'brave-ui/theme'
import Theme from 'brave-ui/theme/brave-default'
import { getActions as getUtilActions, getCurrentBalanceReport, setActions } from './utils'
import * as rewardsActions from './actions/rewards_actions'

window.cr.define('brave_rewards', function () {
  'use strict'

  function initialize () {
    window.i18nTemplate.process(window.document, window.loadTimeData)
    if (window.loadTimeData && window.loadTimeData.data_) {
      initLocale(window.loadTimeData.data_)
    }

    render(
      <Provider store={store}>
        <ThemeProvider theme={Theme}>
          <App />
        </ThemeProvider>
      </Provider>,
      document.getElementById('root'))
  }

  function getActions () {
    const actions: any = getUtilActions()
    if (actions) {
      return actions
    }
    const newActions = bindActionCreators(rewardsActions, store.dispatch.bind(store))
    setActions(newActions)
    return newActions
  }

  function walletCreated () {
    getActions().onWalletCreated()
  }

  function walletCreateFailed () {
    getActions().onWalletCreateFailed()
  }

  function walletProperties (properties: {status: number, wallet: Rewards.WalletProperties, monthlyAmount: number}) {
    getActions().onWalletProperties(properties)
  }

  function promotions (properties: Rewards.PromotionResponse) {
    getActions().onPromotions(properties)
  }

  function walletPassphrase (pass: string) {
    getActions().onWalletPassphrase(pass)
  }

  function promotionFinish (properties: Rewards.PromotionFinish) {
    getActions().onPromotionFinish(properties)
  }

  function reconcileStamp (stamp: number) {
    getActions().onReconcileStamp(stamp)
  }

  function contributeList (list: Rewards.Publisher[]) {
    getActions().onContributeList(list)
  }

  function excludedList (list: Rewards.ExcludedPublisher[]) {
    getActions().onExcludedList(list)
  }

  function balanceReport (properties: {month: number, year: number, report: Rewards.BalanceReport}) {
    getActions().onBalanceReport(properties)
  }

  function walletExists (exists: boolean) {
    getActions().onWalletExists(exists)
  }

  function contributionAmount (amount: number) {
    getActions().onContributionAmount(amount)
  }

  function recurringTips (list: Rewards.Publisher[]) {
    getActions().onRecurringTips(list)
  }

  function currentTips (list: Rewards.Publisher[]) {
    getActions().onCurrentTips(list)
  }

  function initAutoContributeSettings (properties: any) {
    getActions().onInitAutoContributeSettings(properties)
  }

  function imported (imported: boolean) {
    getActions().onImportedCheck(imported)
  }

  function adsData (adsData: Rewards.AdsData) {
    getActions().onAdsData(adsData)
  }

  function onPendingContributionSaved (result: number) {
    if (result === 0) {
      getActions().getPendingContributions()
    }
  }

  function rewardsEnabled (enabled: boolean) {
    getActions().onRewardsEnabled(enabled)
  }

  function transactionHistory (data: {adsEstimatedPendingRewards: number, adsNextPaymentDate: string, adsNotificationsReceivedThisMonth: number}) {
    getActions().onTransactionHistory(data)
  }

  function transactionHistoryChanged () {
    getActions().onTransactionHistoryChanged()
  }

  function recurringTipSaved (success: boolean) {
    getActions().onRecurringTipSaved(success)
  }

  function recurringTipRemoved (success: boolean) {
    getActions().onRecurringTipRemoved(success)
  }

  function pendingContributions (list: Rewards.PendingContribution[]) {
    getActions().onPendingContributions(list)
  }

  function onRemovePendingContribution (result: number) {
    if (result === 0) {
      getActions().getPendingContributions()
    }
  }

  function excludedSiteChanged () {
    getActions().getExcludedSites()
    getActions().getContributeList()
  }

  function balance (properties: {status: number, balance: Rewards.Balance}) {
    getActions().onBalance(properties.status, properties.balance)
  }

  function reconcileComplete (properties: {type: number, result: number}) {
    chrome.send('brave_rewards.getReconcileStamp')
    getActions().getContributeList()
    getActions().getBalance()
    getActions().getWalletProperties()
    getCurrentBalanceReport()

    if (properties.type === 8) { // Rewards.RewardsType.ONE_TIME_TIP
      chrome.send('brave_rewards.getOneTimeTips')
    }
  }

  function onlyAnonWallet (only: boolean) {
    getActions().onOnlyAnonWallet(only)
  }

  function unblindedTokensReady () {
    getActions().getBalance()
  }

  return {
    initialize,
    walletCreated,
    walletCreateFailed,
    walletProperties,
    promotions,
    walletPassphrase,
    promotionFinish,
    reconcileStamp,
    contributeList,
    excludedList,
    balanceReport,
    walletExists,
    contributionAmount,
    recurringTips,
    currentTips,
    initAutoContributeSettings,
    imported,
    adsData,
    pendingContributions,
    onPendingContributionSaved,
    rewardsEnabled,
    transactionHistory,
    transactionHistoryChanged,
    recurringTipSaved,
    recurringTipRemoved,
    onRemovePendingContribution,
    excludedSiteChanged,
    balance,
    reconcileComplete,
    onlyAnonWallet,
    unblindedTokensReady
  }
})

document.addEventListener('DOMContentLoaded', window.brave_rewards.initialize)
