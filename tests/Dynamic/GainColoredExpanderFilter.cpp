/**
 * \ file GainColoredExpanderFilter.cpp
 */

#include <ATK/Dynamic/GainColoredExpanderFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 64;

TEST(GainColoredExpanderFilter, softness_test)
{
  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter;
  filter.set_softness(0.5);
  ASSERT_EQ(filter.get_softness(), 0.5);
}

TEST(GainColoredExpanderFilter, softness_range_test)
{
  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter;
  ASSERT_THROW(filter.set_softness(-0.000001), ATK::RuntimeError);
}

TEST(GainColoredExpanderFilter, color_test)
{
  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter;
  filter.set_color(0.5);
  ASSERT_EQ(filter.get_color(), 0.5);
}

TEST(GainColoredExpanderFilter, quality_test)
{
  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter;
  filter.set_quality(0.5);
  ASSERT_EQ(filter.get_quality(), 0.5);
}

TEST(GainColoredExpanderFilter, quality_range_test)
{
  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter;
  ASSERT_THROW(filter.set_quality(0), ATK::RuntimeError);
}

TEST(GainColoredExpanderFilter, const_1_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter(1);
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

TEST(GainColoredExpanderFilter, const_0_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(outdata[i], 0, 0.001);
  }
}

TEST(GainColoredExpanderFilter, const_1_threshold_2_ratio_2_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_ratio(2);
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

TEST(GainColoredExpanderFilter, const_1_threshold_2_ratio_4_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_ratio(4);
  filter.set_softness(1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.343814075, outdata[i], 0.1);
  }
}

TEST(GainColoredExpanderFilter, always_more_1_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = i/1024.;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::array<double, PROCESSSIZE> outdata;
  
  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(1);
  filter.set_quality(.1);
  filter.set_color(.1);
  
  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);
  
  output.process(PROCESSSIZE);
  
  for(gsl::index i = 1; i < PROCESSSIZE; ++i)
  {
    ASSERT_GE(outdata[i], 1 - 10 * std::numeric_limits<float>::epsilon());
  }
}

TEST(GainColoredExpanderFilter, always_less_1_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = i/1024.;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::array<double, PROCESSSIZE> outdata;
  
  ATK::GainFilter<ATK::GainColoredExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(1);
  filter.set_quality(.1);
  filter.set_color(-.1);
  
  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);
  
  output.process(PROCESSSIZE);
  
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_LE(outdata[i], 1 + 10 * std::numeric_limits<float>::epsilon());
  }
}
