/**
 * \file TanFilter.cpp
 */

#include <ATK/Tools/TanFilter.h>

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType_>
  TanFilter<DataType_>::TanFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels), coeff(1)
  {
    
  }
  
  template<typename DataType_>
  TanFilter<DataType_>::~TanFilter()
  {
    
  }
  
  template<typename DataType_>
  void TanFilter<DataType_>::setup()
  {
    coeff = boost::math::constants::pi<DataType_>() / input_sampling_rate;
  }
  
  template<typename DataType_>
  void TanFilter<DataType_>::process_impl(gsl::index size) const
  {
    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        output[i] = static_cast<DataType>(tan(input[i] * coeff));
      }
    }
  }
  
  template class TanFilter<float>;
  template class TanFilter<double>;
}
