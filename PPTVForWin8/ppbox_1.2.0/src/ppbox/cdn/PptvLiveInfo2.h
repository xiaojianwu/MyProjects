// PptvLiveInfo2.h

#ifndef _PPBOX_CDN_PPTV_LIVE_INFO2_H_
#define _PPBOX_CDN_PPTV_LIVE_INFO2_H_

#include "ppbox/cdn/PptvLiveInfo.h"

namespace ppbox
{
    namespace cdn
    {

        struct Live2JumpInfo
        {
            Jump jump;
            LiveVideo video;
            boost::uint32_t delay_play_time;

            template <
                typename Archive
            >
            void serialize(
                Archive & ar)
            {
                ar.version(live_2);
                ar & jump
                    & video
                    & SERIALIZATION_NVP(delay_play_time);
                delay_play_time *= 1000;
            }
        };

    } // namespace cdn
} // namespace ppbox

#endif//_PPBOX_CDN_PPTV_LIVE_INFO2_H_
