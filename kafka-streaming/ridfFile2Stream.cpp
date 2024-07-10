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
            ridf.seekg(ridf.tellg() - kWordSize);
            // std::cout << "read block: " << block_size << ", class id: " << class_id << ", layer: " << layer << std::endl;
        };

        // Read header and get the block size
        readHeader(block_size, class_id, layer);

        // Break if the block size is greater than EoF
        if (ridf.tellg() + block_size * 2 > size)
            break;

        // Break if the block size is zero
        if (!block_size)
            break;

        // Read the block
        auto buff = std::make_unique<char[]>(block_size * 2);
        ridf.read(buff.get(), block_size * 2);

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