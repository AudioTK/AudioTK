/**
 * \ file DerivativeFilter.cpp
 */

#include <array>
#include <fstream>

#include <ATK/config.h>

#include <ATK/Tools/DerivativeFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#include <boost/math/constants/constants.hpp>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1000;
constexpr gsl::index SAMPLING_RATE = 2*1024*1024;
constexpr gsl::index freq = 1024;
constexpr gsl::index offset = SAMPLING_RATE / (4 * freq);

TEST(DerivativeFilter, const_sin1k)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLING_RATE);
  generator.set_amplitude(1);
  generator.set_frequency(freq);
  
  ATK::DerivativeFilter<double> filter;
  filter.set_input_sampling_rate(SAMPLING_RATE);
  filter.set_output_sampling_rate(SAMPLING_RATE);
  
  filter.set_input_port(0, generator, 0);
  filter.process(PROCESSSIZE);
  
  auto sin = generator.get_output_array(0);
  auto array = filter.get_output_array(0);
  
  auto coeff = 2 * freq * boost::math::constants::pi<double>() / SAMPLING_RATE;
  
  for(size_t i = 1; i < PROCESSSIZE - offset; ++i)
  {
    ASSERT_NEAR(array[i], coeff * sin[i + offset], 5);
  }
}
