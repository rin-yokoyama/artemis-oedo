#ifndef __TSIMPLE_DATA_BUILDER_HPP__
#define __TSIMPLE_DATA_BUILDER_HPP__
#include "TDataBuilderBase.hpp"
#include "TSimpleData.h"
#include <TClonesArray.h>
#include <TIterator.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>

namespace art
{
    class TSimpleDataBuilder;
}

class art::TSimpleDataBuilder : public art::TDataBuilderBase
{
public:
    TSimpleDataBuilder(const std::string &name);
    ~TSimpleDataBuilder(){};

    void FillArrow(const TClonesArray &input) override;

    /**
     * @brief Finalize arrow builders and append fields and arrays
     *
     * @param fields reference to the FieldVector for generating data schema
     * @param arrays reference to the ArrayVector for generating data table
     */
    void Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays) override;

    // Arrow Builders
    std::shared_ptr<arrow::FloatBuilder> value_builder_;
    std::shared_ptr<arrow::ListBuilder> list_value_builder_;
};
#endif /*__TTIMING_CHARGE_DATA_BUILDER_HPP__*/