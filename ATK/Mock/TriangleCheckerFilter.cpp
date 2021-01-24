/**
 * \file TriangleCheckerFilter.cpp
 */

#include "TriangleCheckerFilter.h"
#include <ATK/Core/TypeTraits.h>

#include <gtest/gtest.h>

#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdlib>
#include <type_traits>

namespace
{
  template<class DataType>
  void compare(DataType v1, DataType v2)
  {
    if constexpr(std::is_integral<DataType>::value)
    {
      ASSERT_EQ(v1, v2);
    }
    else
    {
      if(std::abs(v1) < 1e-5 || std::abs(v2) < 1e-5)
      {
        auto absv1 = std::abs(v1);
        auto absv2 = std::abs(v2);
        ASSERT_NEAR(absv1, 0, typename ATK::TypeTraits<DataType>::Scalar(1e-5));
        ASSERT_NEAR(absv2, 0, typename ATK::TypeTraits<DataType>::Scalar(1e-5));
      }
      else
      {
        auto diff = std::abs((v1 - v2) / (v1 + v2));
        ASSERT_NEAR(diff, 0, typename ATK::TypeTraits<DataType>::Scalar(1e-5));
      }
    }
  }
}

namespace ATK
{
  template<class DataType_>
  TriangleCheckerFilter<DataType_>::TriangleCheckerFilter()
  :TypedBaseFilter<DataType_>(1, 0)
  {
  }
  
  template<class DataType_>
  void TriangleCheckerFilter<DataType_>::set_amplitude(DataType_ amplitude)
  {
    this->amplitude = amplitude;
  }
  
  template<class DataType_>
  void TriangleCheckerFilter<DataType_>::set_frequency(int frequency)
  {
    this->frequency = frequency;
  }

  template<class DataType_>
  void TriangleCheckerFilter<DataType_>::process_impl(gsl::index size) const
  {
    double real_increment = 2. / input_sampling_rate * frequency;
    
    for(gsl::index i = 0; i < size; ++i)
    {
      state += real_increment * (ascending ? 1 : -1);
      if(state >= 1)
      {
        state -= 2 * real_increment;
        ascending = !ascending;
      }
      else if(state <= -1)
      {
        state += 2 * real_increment;
        ascending = !ascending;
      }
      compare(converted_inputs[0][i], TypeTraits<DataType>::from_double(TypeTraits<DataType>::to_double(amplitude) * state));
    }
  }

  template class TriangleCheckerFilter<std::int16_t>;
  template class TriangleCheckerFilter<std::int32_t>;
  template class TriangleCheckerFilter<std::int64_t>;
  template class TriangleCheckerFilter<float>;
  template class TriangleCheckerFilter<double>;
  template class TriangleCheckerFilter<std::complex<float>>;
  template class TriangleCheckerFilter<std::complex<double>>;
}
