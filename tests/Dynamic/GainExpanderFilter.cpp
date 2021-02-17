/**
 * \ file GainExpanderFilter.cpp
 */

#include <ATK/Dynamic/GainExpanderFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 64;

TEST(GainExpanderFilter, softness_test)
{
  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter;
  filter.set_softness(0.5);
  ASSERT_EQ(filter.get_softness(), 0.5);
}

TEST(GainExpanderFilter, softness_range_test)
{
  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter;
  ASSERT_THROW(filter.set_softness(-0.000001), ATK::RuntimeError);
}

TEST(GainExpanderFilter, const_1_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(1, outdata[i], 0.1);
  }
}

TEST(GainExpanderFilter, const_0_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.1);
  filter.set_ratio(2);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(outdata[i], 0, 0.001);
  }
}

TEST(GainExpanderFilter, const_1_threshold_2_ratio_2_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter(1);
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

TEST(GainExpanderFilter, const_1_threshold_2_ratio_2_test_LUT)
{
  std::array<double, PROCESSSIZE> data;
  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_ratio(2);
  filter.set_softness(1);
  filter.wait_for_LUT_completion();

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.700553358, outdata[i], 0.1);
  }
}

TEST(GainExpanderFilter, const_1_threshold_2_ratio_4_test)
{
  std::array<double, PROCESSSIZE> data;
  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_ratio(4);
  filter.set_softness(1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.343814075, outdata[i], 0.1);
  }
}

TEST(GainExpanderFilter, const_1_threshold_2_ratio_4_test_LUT)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_ratio(4);
  filter.set_softness(1);
  filter.wait_for_LUT_completion();

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.343814075, outdata[i], 0.1);
  }
}

TEST(GainExpanderFilter, const_1_threshold_2_ratio_4_test_twice)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::array<double, PROCESSSIZE> outdata;
  
  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter(1);
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
  
  generator.set_pointer(data.data(), PROCESSSIZE);
  output.set_pointer(outdata.data(), PROCESSSIZE);
  
  output.process(PROCESSSIZE);
  
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.343814075, outdata[i], 0.1);
  }
}

TEST(GainExpanderFilter, const_1_threshold_2_ratio_4_test_twice_LUT)
{
  std::array<double, PROCESSSIZE> data;
  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainExpanderFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(2);
  filter.set_ratio(4);
  filter.set_softness(1);
  filter.wait_for_LUT_completion();

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.343814075, outdata[i], 0.1);
  }

  generator.set_pointer(data.data(), PROCESSSIZE);
  output.set_pointer(outdata.data(), PROCESSSIZE);

  output.process(PROCESSSIZE);

  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.343814075, outdata[i], 0.1);
  }
}
