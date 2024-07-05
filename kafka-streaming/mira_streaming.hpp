#ifndef __MIRA_STREAMING__
#define __MIRA_STREAMING__

// #include "mira_constants.h"
#include <librdkafka/rdkafka.h>
#include <functional>
#include <string>

namespace mira
{
    void polling_loop(const std::string &client_id, const std::string &bootstrap_servers, const std::string &group_id, const std::string &topic_names, std::function<void(size_t, void *)> func)
    {
        // Initialize a Kafka consumer
        char errstr[512];
        rd_kafka_conf_t *conf = rd_kafka_conf_new();
        rd_kafka_conf_set(conf, "client.id", client_id.c_str(), errstr, sizeof(errstr));
        rd_kafka_conf_set(conf, "group.id", group_id.c_str(), errstr, sizeof(errstr));
        rd_kafka_conf_set(conf, "bootstrap.servers", bootstrap_servers.c_str(), errstr, sizeof(errstr));
        rd_kafka_topic_conf_t *tconf = rd_kafka_topic_conf_new();
        rd_kafka_topic_conf_set(tconf, "auto.offset.reset", "latest", errstr, sizeof(errstr));
        rd_kafka_conf_set_default_topic_conf(conf, tconf);
        rd_kafka_t *rk;
        rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
        rd_kafka_poll_set_consumer(rk);
        rd_kafka_topic_partition_list_t *topics = rd_kafka_topic_partition_list_new(1);
        rd_kafka_topic_partition_list_add(topics, topic_names.c_str(), RD_KAFKA_PARTITION_UA);

        auto err = rd_kafka_subscribe(rk, topics);
        if (err)
            std::cout << rd_kafka_err2str(err) << std::endl;
        rd_kafka_topic_partition_list_destroy(topics);

        // polling loop
        while (true)
        {
            rd_kafka_message_t *rkmessage = rd_kafka_consumer_poll(rk, 500);
            if (rkmessage)
            {
                if (rkmessage->err == RD_KAFKA_RESP_ERR__PARTITION_EOF)
                    continue; // The partition is empty
                if (rkmessage->err)
                {
                    std::cout << rd_kafka_err2str(rkmessage->err) << std::endl;
                    break;
                }
                size_t size = rkmessage->len;
                void *buffer = (u_int32_t *)rkmessage->payload;
                func(size, buffer);
                rd_kafka_message_destroy(rkmessage);
            }
        }
    }

    rd_kafka_topic_t *init_producer(const std::string &client_id, const std::string &bootstrap_servers, const std::string &topic_names)
    {
        char errstr[512];
        rd_kafka_conf_t *conf = rd_kafka_conf_new();
        rd_kafka_conf_set(conf, "client.id", client_id.c_str(), errstr, sizeof(errstr));
        rd_kafka_conf_set(conf, "bootstrap.servers", bootstrap_servers.c_str(), errstr, sizeof(errstr));
        rd_kafka_topic_conf_t *topic_conf = rd_kafka_topic_conf_new();
        rd_kafka_t *rk_p = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));
        rd_kafka_topic_t *topics = rd_kafka_topic_new(rk_p, topic_names.c_str(), topic_conf);
        return topics;
    }

    void produce(rd_kafka_topic_t *topic, size_t payload_len, void *payload)
    {
        rd_kafka_produce(topic, RD_KAFKA_PARTITION_UA, RD_KAFKA_MSG_F_COPY, payload, payload_len, NULL, 0, NULL);
    }

};

#endif