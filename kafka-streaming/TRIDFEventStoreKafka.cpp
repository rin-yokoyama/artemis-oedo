/**
 * @file TRIDFEventStoreKafka.cpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief
 * @version 0.1
 * @date 2024-07-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "TRIDFEventStoreKafka.hpp"
#include <TRunInfo.h>
#include <TEventHeader.h>
#include <TSegmentedData.h>
#include <TModuleDecoderFactory.h>
#include <TTimestampEventList.h>
#include <TDataSource.h>
art::TRIDFEventStoreKafka::TRIDFEventStoreKafka() : TRIDFEventStore()
{
    RegisterProcessorParameter<TString>("BootstrapServers", "Kafka parameter: bootstrap.servers", bootstrap_servers_, "localhost:9092");
    RegisterProcessorParameter<TString>("TopicName", "Kafka parameter: topic", topic_name_, "test");
    RegisterProcessorParameter<TString>("GroupId", "Kafka parameter: group.id", group_id_, "0");
    RegisterProcessorParameter<TString>("ClientId", "Kafka parameter: client.id", client_id_, "0");
    RegisterProcessorParameter<TString>("Timestamp", "Kafka parameter: timestamp", timestamp_, "0");
    RegisterProcessorParameter<TString>("Timeout", "Time out to stop in sec.", timeout_, "10");
}

art::TRIDFEventStoreKafka::~TRIDFEventStoreKafka() {}

void art::TRIDFEventStoreKafka::Init(TEventCollection *col)
{
    art::TRIDFEventStore::Init(col);
    std::cout << "TRIDFEventStoreKafka: bootstrap_servers_ = " << bootstrap_servers_ << std::endl;
    std::cout << "TRIDFEventStoreKafka: topic_name_ = " << topic_name_ << std::endl;
    std::cout << "TRIDFEventStoreKafka: timestamp_ = " << timestamp_ << std::endl;
    if (!Open())
        std::cerr << "TRIDFEventStoreKafka: Cannot open DataSource" << std::endl;
    timeout_sec_ = std::atoi(timeout_);
}

Bool_t art::TRIDFEventStoreKafka::GetNextBlock()
{
    if (!fDataSource)
    {
        // data source is not ready
        return kFALSE;
    }

    fBlockSize = fDataSource->Read(fBuffer, 0);
    if (!fBlockSize)
    {
        return kFALSE;
    }
    fOffset = 8; // Start after the block header
    fIsEOB = kFALSE;
    return kTRUE;
}

void art::TRIDFEventStoreKafka::Process()
{
    // art::TRIDFEventStore::Process();
    // return;
    //  try to prepare data source
    fRIDFData.fSegmentedData->Clear("C");

    if (fRunStatus->IsSet(TLoop::kEndOfRun))
        return;

    int count = 0;
    while (!GetNextEvent())
    {
        while (!GetNextBlock())
        {
            // check stop condition
            if ((*fCondition)->IsSet(TLoop::kStopLoop))
            {
                SetStopEvent();
                return;
            }
            if (fDataSource->GetStatus() == art::TDataSource::kReady)
                ++count;
            if (count > 10)
                NotifyEndOfRun();
        }
    }
}

Bool_t art::TRIDFEventStoreKafka::Open()
{
    if (fDataSource)
    {
        Error("Open", "Data source is already prepared");
    }
    art::TRunInfo *runinfo = new art::TRunInfo("Kafka", "Kafka");
    runinfo->SetRunName("Kafka");
    runinfo->SetRunNumber(0);
    runinfo->SetStartTime(0);
    runinfo->SetStopTime(0);
    runinfo->SetHeader("");
    runinfo->SetEnder("");
    fRIDFData.fRunHeaders->Add(runinfo);
    fRIDFData.fEventHeader->SetRunName("Kafka");
    fRIDFData.fEventHeader->SetRunNumber(0);
    ULong64_t ts = std::atoll(timestamp_.Data());
    fDataSource = new art::TKafkaDataSource(std::string(bootstrap_servers_), std::string(topic_name_), std::string(group_id_), std::string(client_id_), ts);
    if (!fDataSource)
        return kFALSE;
    if (fDataSource->IsPrepared())
    {
        return kTRUE;
    }
    else
        return kFALSE;
}

Bool_t art::TRIDFEventStoreKafka::GetNextEvent()
{
    if (fIsEOB)
        return kFALSE;
    // parse data if available
    while (1)
    {
        Bool_t doSkip = kFALSE;
        fRIDFData.fDecoderFactory->Clear();
        memcpy(&fHeader, fBuffer + fOffset, sizeof(fHeader));
        if (fHeader.ClassID() == 0)
        {
            fIsEOB = kTRUE;
            return kFALSE;
        }

        //////////////////////////////////////////////////////////////////////
        // judge if event segment is analyzed or not
        //////////////////////////////////////////////////////////////////////
        if (fHeader.ClassID() == 3 ||
            fHeader.ClassID() == 6)
        {

            if (fStartEventNumber > fRIDFData.fEventHeader->GetEventNumber())
            {
                doSkip = kTRUE;
            }

            fRIDFData.fEventHeader->IncrementEventNumber();
            ((TRunInfo *)fRIDFData.fRunHeaders->Last())->IncrementEventNumber();
            if (fEventList)
            {
                if (fInputEventNumber.IsInitialized())
                {
                    fEventListIndex = fInputEventNumber->GetValue();
                }
                Int_t eventNumber = fEventList->GetEntry(fEventListIndex);
                //            printf("#event = %d, index = %d\n",eventNumber,fEventListIndex);
                // set EOB and return false if no event exists
                if (eventNumber < 0)
                {
                    NotifyEndOfRun();
                    fIsEOB = kTRUE;
                    return kTRUE;
                }
                // skip event if event number mismatch
                if (fRIDFData.fEventHeader->GetEventNumber() != eventNumber)
                {
                    //               Info("GetNextEvent","skip");
                    //               ClassDecoderSkip(fBuffer,fOffset,&fRIDFData);
                    doSkip = kTRUE;
                }
            }
            if (!doSkip)
            {
                fEventListIndex++;
            }
#ifdef USE_MPI
            {
                if (fUseMPI)
                {
                    // skip if modulus of event serial number to total number of processor is not equal to rank
                    if (!fInputEventNumber.IsInitialized() && (fEventListIndex % fNPE) != fRankID)
                    {
                        doSkip = kTRUE;
                    }
                }
            }
#endif
            if (!doSkip)
            {
                if (fOutputEventNumber.IsInitialized())
                    fOutputEventNumber->SetValue(fEventListIndex - 1);
            }
        }

        if (doSkip)
        {
            ClassDecoderSkip(fBuffer, fOffset, &fRIDFData);
        }
        else if (fClassDecoder[fHeader.ClassID()])
        {
            fClassDecoder[fHeader.ClassID()](fBuffer, fOffset, &fRIDFData);
        }
        else
        {
            printf("Class ID = %d\n", fHeader.ClassID());
            ClassDecoderUnknown(fBuffer, fOffset, &fRIDFData);
        }
        if (fOffset >= fBlockSize)
        {
            fIsEOB = kTRUE;
        }
        // TClassDecoder::Decode(fBuffer,fOffset,fNext,something?)
        // if the data is available or not
        if (fRIDFData.fSegmentedData->GetEntriesFast())
        {
            // the data is available
            return kTRUE;
        }
        else if (fIsEOB)
        {
            // no data is available
            return kFALSE;
        }
    }
}