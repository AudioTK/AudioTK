/**
 * \ file SinusGeneratorFilter.cpp
 */

#include <ATK/config.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>
#include <ATK/Tools/SinusGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024;

TEST(SinusGeneratorFilter, volume_test)
{
  ATK::SinusGeneratorFilter<double> filter;
  filter.set_volume(10);
  ASSERT_EQ(filter.get_volume(), 10);
}

TEST(SinusGeneratorFilter, offset_test)
{
  ATK::SinusGeneratorFilter<double> filter;
  filter.set_offset(10);
  ASSERT_EQ(filter.get_offset(), 10);
}

TEST(SinusGeneratorFilter, frequency_test)
{
  ATK::SinusGeneratorFilter<double> filter;
  filter.set_frequency(100);
  ASSERT_EQ(filter.get_frequency(), 100);
}

TEST(SinusGeneratorFilter, frequency_range_test)
{
  ATK::SinusGeneratorFilter<double> filter;
  ASSERT_THROW(filter.set_frequency(0), std::out_of_range);
}

TEST(SinusGeneratorFilter, 1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(-1);
  generator.set_frequency(1000);
  
  ATK::SinusGeneratorFilter<double> filter;
  filter.set_output_sampling_rate(48000);
  filter.set_frequency(1000);

  ATK::SumFilter<double> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  sumfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(1, &filter, 1);
  
  checker.set_input_port(0, &sumfilter, 0);
  
  checker.process(PROCESSSIZE);
}
