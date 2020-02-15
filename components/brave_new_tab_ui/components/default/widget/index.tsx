/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { StyledWidget, StyledWidgetContainer } from './styles'
import WidgetMenu from './widgetMenu'

type HideWidgetFunction = () => void

export interface WidgetProps {
  menuPosition: 'right' | 'left'
  hideWidget?: HideWidgetFunction
  preventFocus?: boolean
  textDirection: string
}

export interface WidgetState {
  widgetMenuPersist: boolean
}

const createWidget = <P extends object>(WrappedComponent: React.ComponentType<P>) =>
  class Widget extends React.Component<P & WidgetProps, WidgetState> {
    constructor (props: P & WidgetProps) {
      super(props)
      this.state = {
        widgetMenuPersist: false
      }
    }

    toggleWidgetHover = () => {
      this.setState({ widgetMenuPersist: !this.state.widgetMenuPersist })
    }

    unpersistWidgetHover = () => {
      this.setState({ widgetMenuPersist: false })
    }

    render () {
      const { menuPosition, hideWidget, textDirection, preventFocus } = this.props
      const { widgetMenuPersist } = this.state

      return (
        <StyledWidgetContainer
          menuPosition={menuPosition}
          textDirection={textDirection}
        >
          <StyledWidget
            widgetMenuPersist={widgetMenuPersist}
            preventFocus={preventFocus}
          >
              <WrappedComponent {...this.props as P}/>
          </StyledWidget>
          {hideWidget && !preventFocus &&
          <WidgetMenu
            widgetMenuPersist={widgetMenuPersist}
            toggleWidgetHover={this.toggleWidgetHover}
            textDirection={textDirection}
            menuPosition={menuPosition}
            hideWidget={hideWidget as HideWidgetFunction}
            unpersistWidgetHover={this.unpersistWidgetHover}
          />
          }
        </StyledWidgetContainer>
      )
    }
  }

export default createWidget
