#include "TDataBuilderBase.hpp"

art::TDataBuilderBase::TDataBuilderBase(const std::string &name)
{
    pool_ = arrow::default_memory_pool();
    name_ = name;
}