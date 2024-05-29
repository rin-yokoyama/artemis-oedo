#include "TSimpleDataBuilder.hpp"

art::TSimpleDataBuilder::TSimpleDataBuilder(const std::string &name) : TDataBuilderBase(name)
{
    value_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    list_value_builder_ = std::make_shared<arrow::ListBuilder>(pool_, value_builder_);
}

void art::TSimpleDataBuilder::FillArrow(const TClonesArray &input)
{
    PARQUET_THROW_NOT_OK(list_value_builder_->Append());
    if (!input.GetEntriesFast())
        return;
    TIter next(&input);
    while (auto obj = next())
    {
        auto data = (art::TSimpleData *)obj;
        PARQUET_THROW_NOT_OK(value_builder_->Append(data->GetValue()));
    }
}

void art::TSimpleDataBuilder::Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays)
{
    std::shared_ptr<arrow::Array> list_value_array;
    PARQUET_THROW_NOT_OK(list_value_builder_->Finish(&list_value_array));

    fields.emplace_back(arrow::field(name_ + ".fValue", arrow::list(arrow::float32())));
    arrays.emplace_back(list_value_array);
    return;
}