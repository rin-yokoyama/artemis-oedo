/**
 * @file TRIDFEventStoreKafka.hpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief RIDFEventStore with Kafka streaming
 *  Could be implemented directly in TRIDFEventStore in future
 * @version 0.1
 * @date 2024-07-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef __TRIDF_EVENT_STORE_KAFKA_HPP__
#define __TRIDF_EVENT_STORE_KAFKA_HPP__

#include <TRIDFEventStore.h>
#include "TKafkaDataSource.hpp"

namespace art
{
    class TRIDFEventStoreKafka;

}

class art::TRIDFEventStoreKafka : public TRIDFEventStore
{

public:
    TRIDFEventStoreKafka();
    virtual ~TRIDFEventStoreKafka();

    virtual void Init(TEventCollection *col);
    virtual void Process();
    //  virtual void PreLoop();
    //  virtual void PostLoop();

    // Int_t GetRunNumber() const;
    // const char *GetRunName() const;

protected:
    virtual Bool_t Open();
    virtual Bool_t GetNextBlock();
    virtual Bool_t GetNextEvent();
    TString bootstrap_servers_;
    TString topic_name_;
    TString group_id_;
    TString client_id_;
    TString timeout_;
    TString timestamp_;
    int timeout_sec_;
    // virtual Bool_t GetNextEvent();
    // virtual void NotifyEndOfRun();

public:
    ClassDef(TRIDFEventStoreKafka, 1); // Event store for ridf format files
};
#endif // __TRIDF_EVENT_STORE_HPP__