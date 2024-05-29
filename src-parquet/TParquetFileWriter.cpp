#include "TParquetFileWriter.hpp"

art::TParquetFileWriter::TParquetFileWriter(std::shared_ptr<ROOT::RDataFrame> df)
{
    data_frame_ = df;
    pool_ = arrow::default_memory_pool();
}

void art::TParquetFileWriter::AddBuilder(std::shared_ptr<art::TDataBuilderBase> builder)
{
    auto names = data_frame_->GetColumnNames();
    for (const auto &name : names)
    {
        if (name == builder->GetName())
        {
            builder_vec_.emplace_back(builder);
            return;
        }
    }
    std::cout << "There is no column named " << builder->GetName() << " exists. Skip filling the column." << std::endl;
}

void art::TParquetFileWriter::Fill()
{

    // Fill arrow for each builder
    for (const auto builder : builder_vec_)
    {
        std::cout << "Filling " << builder->GetName() << " to arrow." << std::endl;
        data_frame_->Foreach([&](const TClonesArray &input)
                             { builder->FillArrow(input); }, {builder->GetName()});
    }

    // Finalize the arrays
    arrow::FieldVector fieldVector;
    arrow::ArrayVector arrayVector;
    for (const auto builder : builder_vec_)
    {
        builder->Finalize(fieldVector, arrayVector);
    }

    // Create the table
    std::shared_ptr<arrow::Schema> schema = arrow::schema(fieldVector);
    table_ = arrow::Table::Make(schema, arrayVector);
}

void art::TParquetFileWriter::Write(const std::string &fname)
{
    // Write to file
    std::shared_ptr<arrow::io::FileOutputStream> outfile;
    PARQUET_ASSIGN_OR_THROW(
        outfile,
        arrow::io::FileOutputStream::Open(fname));

    PARQUET_THROW_NOT_OK(
        parquet::arrow::WriteTable(*table_, pool_, outfile));
}