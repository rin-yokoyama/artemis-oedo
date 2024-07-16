#include <iostream>
#include <fstream>
#include <librdkafka/rdkafka.h>
#include "TRIDFEventStore.h"
#include "mira_streaming.hpp"

// word size for RIDF (=4)
static const size_t kWordSize = 4;

// Global variables for Kafka (assuming they are defined somewhere else)
bool kafka_ready = false; // Placeholder

void readRIDF(std::string ridf_file_name, rd_kafka_topic_t *topic, u_int64_t n_block)
{
    // Open ridf file
    std::ifstream ridf(ridf_file_name, std::ios::binary);
    if (!ridf)
    {
        std::cout << "Cannot open file: " << ridf_file_name << std::endl;
        return;
    }
    std::cout << "File opened: " << ridf_file_name << std::endl;

    // Get total size
    ridf.seekg(0, std::ios::end);
    u_int64_t size = ridf.tellg();
    std::cout << "File size: " << size << " bytes." << std::endl;
    ridf.seekg(0);

    // Get the number of partitions for the topic
    const rd_kafka_metadata_t *metadata;
    if (rd_kafka_metadata(mira::rk_producer, 0, topic, &metadata, 5000) != RD_KAFKA_RESP_ERR_NO_ERROR)
    {
        std::cerr << "Failed to fetch metadata: " << rd_kafka_err2str(rd_kafka_last_error()) << std::endl;
        return;
    }

    int partition_count = metadata->topics[0].partition_cnt;
    std::cout << "Number of partitions: " << partition_count << std::endl;

    u_int64_t block_count = 0;
    while (true)
    {
        // Break if end of file
        if (ridf.eof())
            break;

        u_int32_t block_size;
        u_int32_t class_id;
        u_int32_t layer;

        auto readHeader = [&ridf](u_int32_t &block_size, u_int32_t &class_id, u_int32_t &layer)
        {
            char header[kWordSize];
            ridf.read(header, kWordSize);
            u_int32_t *header32 = (u_int32_t *)header;
            block_size = (header32[0] & 0x003fffff);
            class_id = ((header32[0] & 0x0fc00000) >> 22);
            layer = ((header32[0] & 0x30000000) >> 28);
            ridf.seekg((u_int32_t)ridf.tellg() - kWordSize);
            // std::cout << "read block: " << block_size << ", class id: " << class_id << ", layer: " << layer << std::endl;
        };

        // Read header and get the block size
        readHeader(block_size, class_id, layer);

        // Break if the block size is greater than EoF
        if (((u_int32_t)ridf.tellg() + (2 * block_size)) > size)
            break;

        // Break if the block size is zero
        if (!block_size)
            break;

        // Read the block
        auto buff = std::make_unique<char[]>(block_size * 2);
        ridf.read(buff.get(), block_size * 2);

        if (!block_count)
        {
            for (int i = 0; i < partition_count; ++i)
            {
                if (rd_kafka_produce(
                        topic, i,
                        RD_KAFKA_MSG_F_COPY,
                        buff.get(), block_size * 2,
                        nullptr, 0,
                        nullptr) == -1)
                {
                    std::cerr << "Failed to produce message to partition " << i << ": " << rd_kafka_err2str(rd_kafka_last_error()) << std::endl;
                }
                else
                {
                    std::cout << "Produced message to partition " << i << std::endl;
                }
            }
            // Wait for all messages to be delivered
            std::cout << "Flushing final messages..." << std::endl;
            rd_kafka_flush(mira::rk_producer, 10 * 1000); // Wait for max 10 seconds
            ++block_count;
        }
        else
        {
            // Placeholder for Kafka producer logic
            mira::produce(topic, block_size * 2, buff.get());
            ++block_count;

            if (!(block_count % 1000))
            {
                double progress = (double)ridf.tellg() / (double)size * 100.;
                std::cout << "block_count: " << block_count << ", " << ridf.tellg() << "bytes/" << size << "bytes (" << progress << "\%)" << std::endl;
            }

            //  Break if the block size is greater than EoF
            if (block_count > n_block)
                break;

            if (ridf.tellg() == -1)
                break;
        }
    }
    ridf.close();
    std::cout
        << "Terminating" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        std::cout << "Usage: ridfFile2Stream [input_file] [bootstrap_servers] [topic] [n_block(optional)]" << std::endl;
        return 1;
    }
    std::string input_file_name = argv[1];  // input file name
    std::string bootstrap_servers(argv[2]); // Kafka bootstrap.servers
    std::string topic_name(argv[3]);        // Kafka topic
    u_int64_t n_block = -1;
    if (argc == 5)
        n_block = std::atoi(argv[4]);
    // initialize a Kafka producer
    auto topic = mira::init_producer("0", bootstrap_servers, topic_name);

    // main loop
    readRIDF(input_file_name, topic, n_block);
    rd_kafka_flush(mira::rk_producer, 1000 * 10);
    rd_kafka_topic_destroy(topic);
    rd_kafka_destroy(mira::rk_producer);
    return 0;
}