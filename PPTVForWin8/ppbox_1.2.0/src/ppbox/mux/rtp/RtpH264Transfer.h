// RtpH264Transfer.h

#ifndef _PPBOX_MUX_RTP_RTP_H264_TRANSFER_H_
#define _PPBOX_MUX_RTP_RTP_H264_TRANSFER_H_

#include "ppbox/mux/rtp/RtpTransfer.h"

namespace ppbox
{
    namespace mux
    {

        class RtpH264Transfer
            : public RtpTransfer
        {
        public:
            RtpH264Transfer();

            ~RtpH264Transfer();

        public:
            virtual void config(
                framework::configure::Config & conf);

        public:
            virtual void transfer(
                StreamInfo & info);

            virtual void transfer(
                Sample & sample);

        private:
            boost::uint32_t mtu_size_;
            boost::uint8_t prefix_[3][2];
            boost::uint32_t sample_description_index_;
            boost::uint32_t use_dts_;
        };

    } // namespace mux
} // namespace ppbox

#endif // _PPBOX_MUX_RTP_RTP_H264_TRANSFER_H_
