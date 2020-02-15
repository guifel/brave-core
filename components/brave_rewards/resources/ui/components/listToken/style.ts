/* This Source Code Form is subject to the terms of the Mozilla Public
 * License. v. 2.0. If a copy of the MPL was not distributed with this file.
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import styled from 'brave-ui/theme'
import { Props } from './index'

export const StyledWrapper = styled<Partial<Props>, 'div'>('div')`
  position: relative;
  display: flex;
  border-bottom: ${p => p.border === 'last' ? 'none' : '1px solid #d0d6dc'};
  border-top: ${p => p.border === 'first' ? '1px solid #d0d6dc' : 'none'};
  justify-content: space-between;
  align-items: baseline;
  align-content: flex-start;
  flex-wrap: nowrap;
  font-family: ${p => p.theme.fontFamily.body};
`

export const StyledTitle = styled<{}, 'div'>('div')`
  font-size: 14px;
  line-height: 1.3;
  color: #4b4c5c;
  flex-grow: 1;
  flex-shrink: 1;
  flex-basis: 60%;
  padding: 10px 0px;
`

export const StyledContentWrapper = styled<{}, 'div'>('div')`
  flex-grow: 1;
  flex-shrink: 1;
  flex-basis: 40%;
  text-align: right;

  @media (max-width: 385px) {
    flex-basis: 55%;
  }
`
