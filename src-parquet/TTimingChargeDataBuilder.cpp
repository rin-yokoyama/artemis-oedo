#include "TTimingChargeDataBuilder.hpp"

art::TTimingChargeDataBuilder::TTimingChargeDataBuilder(const std::string &name) : TDataBuilderBase(name)
{
    charge_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    list_charge_builder_ = std::make_shared<arrow::ListBuilder>(pool_, charge_builder_);
    timing_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    list_timing_builder_ = std::make_shared<arrow::ListBuilder>(pool_, timing_builder_);
    id_builder_ = std::make_shared<arrow::Int32Builder>(pool_);
    list_id_builder_ = std::make_shared<arrow::ListBuilder>(pool_, id_builder_);
}

void art::TTimingChargeDataBuilder::FillArrow(const TClonesArray &input)
{
    PARQUET_THROW_NOT_OK(list_charge_builder_->Append());
    PARQUET_THROW_NOT_OK(list_timing_builder_->Append());
    PARQUET_THROW_NOT_OK(list_id_builder_->Append());
    if (!input.GetEntriesFast())
        return;
    TIter next(&input);
    while (auto obj = next())
    {
        auto data = (art::TTimingChargeData *)obj;
        PARQUET_THROW_NOT_OK(charge_builder_->Append(data->GetCharge()));
        PARQUET_THROW_NOT_OK(timing_builder_->Append(data->GetTiming()));
        PARQUET_THROW_NOT_OK(id_builder_->Append(data->GetID()));
    }
}

void art::TTimingChargeDataBuilder::Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays)
{
    std::shared_ptr<arrow::Array> list_charge_array;
    std::shared_ptr<arrow::Array> list_timing_array;
    std::shared_ptr<arrow::Array> list_id_array;
    PARQUET_THROW_NOT_OK(list_charge_builder_->Finish(&list_charge_array));
    PARQUET_THROW_NOT_OK(list_timing_builder_->Finish(&list_timing_array));
    PARQUET_THROW_NOT_OK(list_id_builder_->Finish(&list_id_array));

    fields.emplace_back(arrow::field(name_ + ".fCharge", arrow::list(arrow::float32())));
    fields.emplace_back(arrow::field(name_ + ".fTiming", arrow::list(arrow::float32())));
    fields.emplace_back(arrow::field(name_ + ".fID", arrow::list(arrow::int32())));
    arrays.emplace_back(list_charge_array);
    arrays.emplace_back(list_timing_array);
    arrays.emplace_back(list_id_array);
    return;
}