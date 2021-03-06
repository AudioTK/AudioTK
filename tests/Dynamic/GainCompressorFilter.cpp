/**
 * \ file GainCompressorFilter.cpp
 */

#include <ATK/Dynamic/GainCompressorFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 64;

TEST(GainFilter, threshold_test)
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  filter.set_threshold(10);
  ASSERT_EQ(filter.get_threshold(), 10);
}

TEST(GainFilter, threshold_db_test)
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  filter.set_threshold_db(20);
  ASSERT_EQ(filter.get_threshold(), 100);
}

TEST(GainFilter, threshold_range_test)
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  ASSERT_THROW(filter.set_threshold(0), ATK::RuntimeError);
}

TEST(GainFilter, ratio_test)
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  filter.set_ratio(10);
  ASSERT_EQ(filter.get_ratio(), 10);
}

TEST(GainFilter, ratio_range_test)
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  ASSERT_THROW(filter.set_ratio(0), ATK::RuntimeError);
}

TEST(GainCompressorFilter, softness_test)
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  filter.set_softness(0.5);
  ASSERT_EQ(filter.get_softness(), 0.5);
}

TEST(GainCompressorFilter, softness_range_test)
{
  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
  ASSERT_THROW(filter.set_softness(-0.000001), ATK::RuntimeError);
}

TEST(GainCompressorFilter, const_1_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter;
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

TEST(GainCompressorFilter, const_0_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 0;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
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

TEST(GainCompressorFilter, const_1_threshold_05_ratio_2_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(2);
  filter.set_softness(1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.836990654, outdata[i], 0.1);
  }
}

TEST(GainCompressorFilter, const_1_threshold_05_ratio_2_test_LUT)
{
  std::array<double, PROCESSSIZE> data;
  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(2);
  filter.set_softness(1);
  filter.wait_for_LUT_completion();

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.836990654, outdata[i], 0.1);
  }
}

TEST(GainCompressorFilter, const_1_threshold_05_ratio_4_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(4);
  filter.set_softness(1);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.765739262, outdata[i], 0.1);
  }
}

TEST(GainCompressorFilter, const_1_threshold_05_ratio_4_test_LUT)
{
  std::array<double, PROCESSSIZE> data;
  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = 1;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;

  ATK::GainFilter<ATK::GainCompressorFilter<double>> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_threshold(0.5);
  filter.set_ratio(4);
  filter.set_softness(1);
  filter.wait_for_LUT_completion();

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);

  for (gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(0.765739262, outdata[i], 0.1);
  }
}
