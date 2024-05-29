#ifndef __TSRPPAC_PLANE_DATA_BUILDER_HPP__
#define __TSRPPAC_PLANE_DATA_BUILDER_HPP__
#include "TDataBuilderBase.hpp"
#include "TSRPPACPlaneData.h"
#include <TClonesArray.h>
#include <TIterator.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>

namespace art
{
    class TSRPPACPlaneDataBuilder;
}

class art::TSRPPACPlaneDataBuilder : public art::TDataBuilderBase
{
public:
    TSRPPACPlaneDataBuilder(const std::string &name);
    ~TSRPPACPlaneDataBuilder(){};

    void FillArrow(const TClonesArray &input) override;

    /**
     * @brief Finalize arrow builders and append fields and arrays
     *
     * @param fields reference to the FieldVector for generating data schema
     * @param arrays reference to the ArrayVector for generating data table
     */
    void Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays) override;

    // Arrow Builders
    std::shared_ptr<arrow::FloatBuilder> position_builder_;
    std::shared_ptr<arrow::ListBuilder> list_position_builder_;
};
#endif /*__TTIMING_CHARGE_DATA_BUILDER_HPP__*/