/**
 * @file TDataBuilderBase.hpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief Base class for arrow builder classes
 * @version 0.1
 * @date 2024-05-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef __TDATA_BUILDER_BASE_HPP__
#define __TDATA_BUILDER_BASE_HPP__
#include <iostream>
#include <string>
#include <arrow/api.h>
#include <TClonesArray.h>

namespace art
{
    class TDataBuilderBase;
}

class art::TDataBuilderBase
{
public:
    TDataBuilderBase(const std::string &name);
    virtual ~TDataBuilderBase() {}

    virtual void FillArrow(const TClonesArray &) = 0;
    virtual void Finalize(arrow::FieldVector &, arrow::ArrayVector &) = 0;

    std::string GetName() const { return name_; }

protected:
    arrow::MemoryPool *pool_;
    std::string name_;
};

#endif /*__TDATA_BUILDER_BASE_HPP__*/