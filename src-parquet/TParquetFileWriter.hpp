#ifndef __TPARQUET_FILE_WRITER_HPP__
#define __TPARQUET_FILE_WRITER_HPP__
#include <iostream>
#include <vector>
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/writer.h>
#include <arrow/type.h>
#include <ROOT/RDataFrame.hxx>
#include "TDataBuilderBase.hpp"

namespace art
{
    class TParquetFileWriter;
}

class art::TParquetFileWriter
{
public:
    TParquetFileWriter(std::shared_ptr<ROOT::RDataFrame> df);
    virtual ~TParquetFileWriter(){};

    void AddBuilder(std::shared_ptr<art::TDataBuilderBase> builder);
    void Fill();
    void Write(const std::string &fname);

private:
    std::shared_ptr<arrow::Table> table_;
    arrow::MemoryPool *pool_;
    std::shared_ptr<ROOT::RDataFrame> data_frame_;
    std::vector<std::shared_ptr<art::TDataBuilderBase>> builder_vec_;
};
#endif /*__TPARQUET_FILE_WRITER_HPP__*/