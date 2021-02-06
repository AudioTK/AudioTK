/**
 * \ file FixedDelayLineFilter.cpp
 */

#include <iostream>

#include <ATK/Delay/FixedDelayLineFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = (1024 * 64);

TEST(FixedDelayLineFilter, line100_delay_1_test)
{
  ATK::FixedDelayLineFilter<double> filter(100);
  ASSERT_THROW(filter.set_delay(0), ATK::RuntimeError);
}

TEST(FixedDelayLineFilter, line100_delay_100_test)
{
  ATK::FixedDelayLineFilter<double> filter(100);
  ASSERT_THROW(filter.set_delay(100), ATK::RuntimeError);
}

TEST(FixedDelayLineFilter, sinus_line100_delay50_test)
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::FixedDelayLineFilter<double> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(50);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(1);
  output.process(49);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);
  
  for(gsl::index i = 0; i < 50; ++i)
  {
    ASSERT_EQ(0, outdata[i]);
  }
  
  for(gsl::index i = 50; i < PROCESSSIZE; ++i)
  {
    ASSERT_EQ(data[i - 50], outdata[i]);
  }
}

TEST(FixedDelayLineFilter, sinus_line100_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::FixedDelayLineFilter<double> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(50);
  filter.process(50);

  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 1; i < 100; ++i)
  {
    output.process(i);
  }
}

TEST(FixedDelayLineFilter, sinus_line1000_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);

  ATK::FixedDelayLineFilter<double> filter(1000);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(50);
  filter.process(50);

  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);

  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);

  for (std::size_t i = 50; i < 1000; ++i)
  {
    output.process(i);
  }
}

TEST(FixedDelayLineFilter, sinus_delay_test)
{
  ATK::FixedDelayLineFilter<double> filter(128);
  filter.set_delay(10);
  ASSERT_EQ(filter.get_delay(), 10);
}
