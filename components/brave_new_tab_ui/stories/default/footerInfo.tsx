/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'

// Feature-specific components
import { Link, Navigation, IconLink, PhotoName } from '../../components/default'
import * as S from '../../components/default/page'

// Icons
import { SettingsAdvancedIcon, BookmarkBook, HistoryIcon } from 'brave-ui/components/icons'

// Helpers
import { getLocale } from '../fakeLocale'
import Settings from './settings'

interface Props {
  textDirection: string
  onClickOutside: () => void
  backgroundImageInfo: any
  onClickSettings: () => void
  showSettingsMenu: boolean
  showPhotoInfo: boolean
  toggleShowBackgroundImage: () => void
  toggleShowClock: () => void
  toggleShowStats: () => void
  toggleShowTopSites: () => void
  toggleShowRewards: () => void
  toggleBrandedWallpaperOptIn: () => void
  showBackgroundImage: boolean
  showClock: boolean
  showStats: boolean
  showTopSites: boolean
  showRewards: boolean
  brandedWallpaperOptIn: boolean
}

export default class FooterInfo extends React.PureComponent<Props, {}> {

  render () {
    const {
      textDirection,
      backgroundImageInfo,
      onClickSettings,
      showSettingsMenu,
      showPhotoInfo,
      onClickOutside,
      toggleShowBackgroundImage,
      toggleShowClock,
      toggleShowStats,
      toggleShowTopSites,
      toggleShowRewards,
      toggleBrandedWallpaperOptIn,
      showBackgroundImage,
      showClock,
      showStats,
      showTopSites,
      showRewards,
      brandedWallpaperOptIn
    } = this.props

    return (
      <>
        {showPhotoInfo &&
        <S.GridItemCredits>
          <PhotoName>
            {`${getLocale('photoBy')} `}
            <Link href={backgroundImageInfo.link} rel='noopener' target='_blank'>
              {backgroundImageInfo.author}
            </Link>
          </PhotoName>
        </S.GridItemCredits>
        }
        <S.GridItemNavigation>
          <Navigation>
            <Settings
              textDirection={textDirection}
              showSettingsMenu={showSettingsMenu}
              onClickOutside={onClickOutside}
              onClick={onClickSettings}
              toggleShowBackgroundImage={toggleShowBackgroundImage}
              toggleShowClock={toggleShowClock}
              toggleShowStats={toggleShowStats}
              toggleShowTopSites={toggleShowTopSites}
              toggleBrandedWallpaperOptIn={toggleBrandedWallpaperOptIn}
              toggleShowRewards={toggleShowRewards}
              showBackgroundImage={showBackgroundImage}
              showClock={showClock}
              showStats={showStats}
              showTopSites={showTopSites}
              brandedWallpaperOptIn={brandedWallpaperOptIn}
              showRewards={showRewards}
            />
            <IconLink><SettingsAdvancedIcon /></IconLink>
            <IconLink><BookmarkBook /></IconLink>
            <IconLink><HistoryIcon /></IconLink>
          </Navigation>
        </S.GridItemNavigation>
      </>
    )
  }
}
