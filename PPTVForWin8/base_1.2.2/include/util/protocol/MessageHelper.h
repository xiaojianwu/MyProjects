// MessageHelper.h

#ifndef _UTIL_PROTOCOL_MESSAGE_HELPER_H_
#define _UTIL_PROTOCOL_MESSAGE_HELPER_H_

namespace util
{
    namespace protocol
    {

        template <
            typename MsgT
        >
        class MessageHelper
        {
        public:
            typedef typename MsgT::header_type header_type;

            typedef typename MsgT::i_archive_t i_archive_t;

            typedef typename MsgT::o_archive_t o_archive_t;

            typedef typename MsgT::context_t context_t;

        public:
            MessageHelper(
                i_archive_t & ar, 
                header_type & header, 
                context_t * ctx)
                : ia_(&ar)
                , oa_(NULL)
                , header_(header)
                , ctx_(ar.context())
                , beg_(ar.tellg())
                , data_beg_(0)
                , filling_(0)
            {
                ar.context(ctx);
            }

            MessageHelper(
                o_archive_t & ar, 
                header_type const & header, 
                context_t * ctx)
                : ia_(NULL)
                , oa_(&ar)
                , header_(const_cast<header_type &>(header))
                , ctx_(ar.context())
                , beg_(ar.tellp())
                , data_beg_(0)
                , filling_(0)
            {
                ar.context(ctx);
            }

            ~MessageHelper()
            {
                if (ia_) {
                    std::streamsize end = ia_->tellg();
                    assert(header_.data_size() == (boost::uint32_t)(end - data_beg_ - filling_));
                    ia_->context(ctx_);
                } else {
                    std::streamsize end = oa_->tellp();
                    header_.data_size(end - data_beg_ - filling_);
                    oa_->seekp(beg_);
                    (*oa_) << header_;
                    oa_->seekp(end);
                    oa_->context(ctx_);
                }
            }

        public:
            void begin_data()
            {
                if (ia_)
                    data_beg_ = ia_->tellg();
                else
                    data_beg_ = oa_->tellp();
            }

        protected:
            i_archive_t * ia_;
            o_archive_t * oa_;
            header_type & header_;
            void * ctx_;
            std::streamsize beg_;
            std::streamsize data_beg_;
            std::streamsize filling_; // 填充字节数，不算在 data_size 中，目前 RTMP 会使用
        };

    } // namespace protocol
} // namespace util

#endif // _UTIL_PROTOCOL_MESSAGE_HELPER_H_
