/**
 * \ file OutCircularPointerFilter.cpp
 */

#include <cmath>

#include <boost/math/constants/constants.hpp>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutCircularPointerFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 512;

TEST(OutCircularPointerFloat, sin1k_test)
{
  std::array<float, PROCESSSIZE*200> data;
  for(gsl::index i = 0; i < PROCESSSIZE*200; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), 1, data.size(), false);
  generator.set_output_sampling_rate(48000);

  ATK::OutCircularPointerFilter<float> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);
  
  auto nb_iterations = 4 + ATK::OutCircularPointerFilter<float>::slice_size * ATK::OutCircularPointerFilter<float>::nb_slices / PROCESSSIZE;
  auto max_zero = std::max(gsl::index(0), gsl::index(ATK::OutCircularPointerFilter<float>::out_slice_size));
  gsl::index offset = 0;

  for(int i = 0; i < nb_iterations; ++i)
  {
    output.process(PROCESSSIZE);
    bool process;
    const auto& outdata = output.get_last_slice(process);
    
    if(process && i!=0)
    {
      max_zero = std::max(
          gsl::index(0), gsl::index(ATK::OutCircularPointerFilter<float>::out_slice_size - (i + 1) * PROCESSSIZE));
      offset = std::max(gsl::index(0),
                   (i + 1) * PROCESSSIZE - gsl::index(ATK::OutCircularPointerFilter<float>::out_slice_size))
             - max_zero;
    }
    for(gsl::index j = 0; j < max_zero; ++j)
    {
      ASSERT_EQ(outdata[j], 0);
    }
    for(gsl::index j = max_zero; j < outdata.size(); ++j)
    {
      ASSERT_EQ(outdata[j], data[j + offset]);
    }
  }
}

TEST(OutCircularPointerFloat, sin1k_full_setup_test)
{
  std::array<float, PROCESSSIZE*200> data;
  for(gsl::index i = 0; i < PROCESSSIZE*200; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), 1, data.size(), false);
  generator.set_output_sampling_rate(48000);
  
  ATK::OutCircularPointerFilter<float> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &generator, 0);
  
  auto nb_iterations = 4 + ATK::OutCircularPointerFilter<float>::slice_size * ATK::OutCircularPointerFilter<float>::nb_slices / PROCESSSIZE;
  
  for(int i = 0; i < nb_iterations; ++i)
  {
    output.process(PROCESSSIZE);
    output.full_setup();
    bool process;
    const auto& outdata = output.get_last_slice(process);
    
    for(gsl::index j = 0; j < outdata.size(); ++j)
    {
      ASSERT_EQ(outdata[j], 0);
    }
  }
}
