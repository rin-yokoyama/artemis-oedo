from confluent_kafka import Consumer, TopicPartition, KafkaException
import sys

def get_latest_offsets(consumer, topic):
    partitions = consumer.list_topics(topic).topics[topic].partitions.keys()
    # Create TopicPartition objects with the latest offset (represented by -1)
    topic_partitions = [TopicPartition(topic, p, -1) for p in partitions]
    # Use get_watermark_offsets to fetch the high watermark which represents the last committed offset
    latest_offsets = {}
    for tp in topic_partitions:
        low, high = consumer.get_watermark_offsets(tp, timeout=5)
        latest_offsets[tp] = high
    return latest_offsets

def get_latest_message_timestamp(consumer, topic):
    latest_offsets = get_latest_offsets(consumer, topic)
    latest_timestamp = None
    latest_partition = None
    
    for tp, offset in latest_offsets.items():
        # We need to fetch the message just before the end offset to get the latest message
        if offset > 0:
            consumer.assign([TopicPartition(tp.topic, tp.partition, offset - 1)])
            msg = consumer.poll(timeout=20.0)
            if msg is None:
                print(f"Timeout while polling for the latest message in partition {tp.partition}")
            elif msg.error():
                print(f"Error while polling for the latest message in partition {tp.partition}: {msg.error()}")
            else:
                msg_timestamp = msg.timestamp()[1]
                if latest_timestamp is None or msg_timestamp > latest_timestamp:
                    latest_timestamp = msg_timestamp
                    latest_partition = tp.partition

    if latest_timestamp is not None and latest_partition is not None:
        print(f"Latest message timestamp is in partition {latest_partition}: {latest_timestamp}")
    else:
        print("No messages found in any partition")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <topic>")
        sys.exit(1)

    topic = sys.argv[1]

    conf = {
        'bootstrap.servers': 'shfs02:9092',
        'group.id': 'artemis',
        'auto.offset.reset': 'latest',  # Set to 'latest' to ignore past messages
        'enable.partition.eof': 'true'
    }

    consumer = Consumer(conf)

    try:
        get_latest_message_timestamp(consumer, topic)
    except KafkaException as e:
        print(f"Kafka error: {e}")
    finally:
        consumer.close()
