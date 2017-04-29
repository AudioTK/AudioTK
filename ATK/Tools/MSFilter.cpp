/**
 * \file MSFilter.cpp
 */

#include "MSFilter.h"

#include <cmath>
#include <complex>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  MiddleSideFilter<DataType_>::MiddleSideFilter()
  :Parent(2, 2)
  {
  }
  
  template<typename DataType_>
  MiddleSideFilter<DataType_>::~MiddleSideFilter()
  {
  }
  
  template<typename DataType_>
  void MiddleSideFilter<DataType_>::process_impl(std::size_t size) const
  {
    const DataType* ATK_RESTRICT input0 = converted_inputs[0];
    const DataType* ATK_RESTRICT input1 = converted_inputs[1];
    DataType* ATK_RESTRICT output0 = outputs[0];
    DataType* ATK_RESTRICT output1 = outputs[1];

    for(std::size_t i = 0; i < size; ++i)
    {
      output0[i] = input0[i] + input1[i];
      output1[i] = input0[i] - input1[i];
    }
  }
  
  template class MiddleSideFilter<std::int16_t>;
  template class MiddleSideFilter<std::int32_t>;
  template class MiddleSideFilter<std::int64_t>;
  template class MiddleSideFilter<float>;
  template class MiddleSideFilter<double>;
  template class MiddleSideFilter<std::complex<float>>;
  template class MiddleSideFilter<std::complex<double>>;
}
