/**
 * @file TKafkaDataSource.hpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief DataSource class for Kafka streaming (with raw data blocks)
 * @version 0.1
 * @date 2024-07-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef __TKAFKA_DATA_SOURCE_HPP__
#define __TKAFKA_DATA_SOURCE_HPP__

#include <iostream>
#include "TDataSource.h"
#include "TSemaphoreObject.h"

#include <librdkafka/rdkafka.h>

namespace art
{
    class TKafkaDataSource;
    struct RdKafkaDeleter
    {
        void operator()(rd_kafka_t *rk) const
        {
            if (rk)
            {
                rd_kafka_destroy(rk);
            }
        }
    };
    struct RdKafkaMessageDeleter
    {
        void operator()(rd_kafka_message_t *msg) const
        {
            if (msg)
            {
                rd_kafka_message_destroy(msg);
            }
        }
    };
}

class art::TKafkaDataSource : public TDataSource
{

public:
    TKafkaDataSource(const std::string &bootstrap_servers, const std::string &topic_name, const std::string &group_id, const std::string &client_id, const ULong64_t &timestamp = 0);
    virtual ~TKafkaDataSource();
    Int_t IsPrepared();
    Int_t Read(Char_t *buf, const Int_t &size);
    Int_t Seek(Long_t offset, Int_t origin);

    Bool_t SetOffset(const ULong64_t &timestamp);

protected:
    const std::string topic_name_;
    std::unique_ptr<rd_kafka_t, art::RdKafkaDeleter> rk_;
    std::unique_ptr<rd_kafka_message_t, art::RdKafkaMessageDeleter> rkmessage_;
};
#endif // __TKAFKA_DATA_SOURCE_HPP__