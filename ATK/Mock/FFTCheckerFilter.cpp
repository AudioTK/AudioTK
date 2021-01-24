/**
 * \file FFTCheckerFilter.cpp
 */

#include "FFTCheckerFilter.h"

#include <gtest/gtest.h>

#include <cmath>

namespace ATK
{
  template<class DataType_>
  FFTCheckerFilter<DataType_>::FFTCheckerFilter()
  :TypedBaseFilter<DataType_>(1, 0)
  {
  }
  
  template<class DataType_>
  FFTCheckerFilter<DataType_>::~FFTCheckerFilter()
  {
  }
  
  template<class DataType_>
  void FFTCheckerFilter<DataType_>::set_checks(const std::vector<std::pair<int, DataType> >& frequency_checks)
  {
    this->frequency_checks = frequency_checks;
  }

  template<class DataType_>
  void FFTCheckerFilter<DataType_>::setup()
  {
    FFTimpl->set_size(input_sampling_rate);
  }
  
  template<class DataType_>
  void FFTCheckerFilter<DataType_>::process_impl(gsl::index size) const
  {
    for(gsl::index i = 0; i < size/input_sampling_rate; ++i)
    {
      FFTimpl->process(converted_inputs[0] + i * input_sampling_rate, input_sampling_rate);
      std::vector<DataType_> output_freqs;
      FFTimpl->get_amp(output_freqs);
      
      for(gsl::index j = 0; j < frequency_checks.size(); ++j)
      {
        DataType amp = output_freqs[frequency_checks[j].first];
        DataType amp_check = frequency_checks[j].second * frequency_checks[j].second;
        if(amp_check < 0.001)
        {
          ASSERT_NEAR(amp, 0, 0.001);
        }
        else
        {
          ASSERT_NEAR(2 * amp, amp_check, 0.1);
        }
      }
    }
  }
  
  template class FFTCheckerFilter<double>;
}
