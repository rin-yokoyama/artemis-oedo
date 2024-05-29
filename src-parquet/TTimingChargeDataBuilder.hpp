#ifndef __TTIMING_CHARGE_DATA_BUILDER_HPP__
#define __TTIMING_CHARGE_DATA_BUILDER_HPP__
#include "TDataBuilderBase.hpp"
#include "TTimingChargeData.h"
#include <TClonesArray.h>
#include <TIterator.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>

namespace art
{
    class TTimingChargeDataBuilder;
}

class art::TTimingChargeDataBuilder : public art::TDataBuilderBase
{
public:
    TTimingChargeDataBuilder(const std::string &name);
    ~TTimingChargeDataBuilder(){};

    void FillArrow(const TClonesArray &input) override;

    /**
     * @brief Finalize arrow builders and append fields and arrays
     *
     * @param fields reference to the FieldVector for generating data schema
     * @param arrays reference to the ArrayVector for generating data table
     */
    void Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays) override;

    // Arrow Builders
    std::shared_ptr<arrow::FloatBuilder> charge_builder_;
    std::shared_ptr<arrow::ListBuilder> list_charge_builder_;
    std::shared_ptr<arrow::FloatBuilder> timing_builder_;
    std::shared_ptr<arrow::ListBuilder> list_timing_builder_;
    std::shared_ptr<arrow::Int32Builder> id_builder_;
    std::shared_ptr<arrow::ListBuilder> list_id_builder_;
};
#endif /*__TTIMING_CHARGE_DATA_BUILDER_HPP__*/