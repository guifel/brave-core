/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import {
  StyledWrapper,
  StyledHeader,
  StyledTitle,
  StyledBalance,
  StyledBalanceTokens,
  StyledBalanceCurrency,
  StyledBalanceConverted
} from './style'
import { getLocale } from 'brave-ui/helpers'

export interface Props {
  id?: string
  balance: string
  converted?: string
  onlyAnonWallet?: boolean
  onClick: () => void
}

export default class WalletInfoHeader extends React.PureComponent<Props, {}> {

  render () {
    const { id, balance, converted, onlyAnonWallet, onClick } = this.props
    const batFormatString = onlyAnonWallet ? getLocale('batPoints') : getLocale('bat')

    return (
      <StyledWrapper
        id={id}
        onClick={onClick}
      >
        <StyledHeader>
          <StyledTitle>{getLocale('yourWallet')}</StyledTitle>
            <StyledBalance>
              <StyledBalanceTokens>
                {balance} <StyledBalanceCurrency>{batFormatString}</StyledBalanceCurrency>
              </StyledBalanceTokens>
              {
                converted
                ? <StyledBalanceConverted>{converted}</StyledBalanceConverted>
                : null
              }
            </StyledBalance>
        </StyledHeader>
      </StyledWrapper>
    )
  }
}
