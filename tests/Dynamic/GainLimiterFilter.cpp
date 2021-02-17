/**
 * \ file GainLimiterFilter.cpp
 */

#include <ATK/Dynamic/GainLimiterFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 64;

TEST(GainLimiterFilter, softness_test)
{
  ATK::GainFilter<ATK::GainLimiterFilter<double>> filter;
  filter.set_softness(0.5);
  ASSERT_EQ(filter.get_softness(), 0.5);
}

TEST(GainLimiterFilter, softness_range_test)
{
  ATK::GainFilter<ATK::GainLimiterFilter<double>> filter;
  ASSERT_THROW(filter.set_softness(-0.000001), ATK::RuntimeError);
}

TEST(GainLimiterFilter, const_1_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainLimiterFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(10);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(1, outdata[i], 0.1);
  }
}

TEST(GainLimiterFilter, const_0_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainLimiterFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(1,
        outdata[i],
        0.1); // if input is zero, we still need a gain of 1 to have a progression of 1 for values < threshold
  }
}

TEST(GainLimiterFilter, const_1_threshold_05_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainLimiterFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_softness(1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.700553358, outdata[i], 0.1);
  }
}
