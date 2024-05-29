#include "TSRPPACPlaneDataBuilder.hpp"

art::TSRPPACPlaneDataBuilder::TSRPPACPlaneDataBuilder(const std::string &name) : TDataBuilderBase(name)
{
    position_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    list_position_builder_ = std::make_shared<arrow::ListBuilder>(pool_, position_builder_);
}

void art::TSRPPACPlaneDataBuilder::FillArrow(const TClonesArray &input)
{
    PARQUET_THROW_NOT_OK(list_position_builder_->Append());
    if (!input.GetEntriesFast())
        return;
    TIter next(&input);
    while (auto obj = next())
    {
        auto data = (art::TSRPPACPlaneData *)obj;
        PARQUET_THROW_NOT_OK(position_builder_->Append(data->GetPosition()));
    }
}

void art::TSRPPACPlaneDataBuilder::Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays)
{
    std::shared_ptr<arrow::Array> list_position_array;
    PARQUET_THROW_NOT_OK(list_position_builder_->Finish(&list_position_array));

    fields.emplace_back(arrow::field(name_ + ".fPosition", arrow::list(arrow::float32())));
    arrays.emplace_back(list_position_array);
    return;
}