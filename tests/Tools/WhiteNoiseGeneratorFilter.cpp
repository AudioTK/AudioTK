/**
 * \ file WhiteNoiseGeneratorFilter.cpp
 */

#include <iostream>

#include <ATK/Tools/WhiteNoiseGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024*1024*4;

TEST(WhiteNoiseGeneratorFilter, volume_test)
{
  ATK::WhiteNoiseGeneratorFilter<double> noisefilter;
  noisefilter.set_volume(10);
  ASSERT_EQ(noisefilter.get_volume(), 10);
}

TEST(WhiteNoiseGeneratorFilter, offset_test)
{
  ATK::WhiteNoiseGeneratorFilter<double> noisefilter;
  noisefilter.set_offset(10);
  ASSERT_EQ(noisefilter.get_offset(), 10);
}

TEST(WhiteNoiseGeneratorFilter, mean_test)
{
  ATK::WhiteNoiseGeneratorFilter<double> noisefilter;
  noisefilter.set_input_sampling_rate(PROCESSSIZE);
  noisefilter.set_output_sampling_rate(PROCESSSIZE);
  noisefilter.process(PROCESSSIZE);

  auto noise = noisefilter.get_output_array(0);
  auto mean = std::accumulate(noise, noise + PROCESSSIZE, 0.) / PROCESSSIZE;
  ASSERT_NEAR(mean, 0, 0.001);
}

TEST(WhiteNoiseGeneratorFilter, std_test)
{
  ATK::WhiteNoiseGeneratorFilter<double> noisefilter;
  noisefilter.set_input_sampling_rate(PROCESSSIZE);
  noisefilter.set_output_sampling_rate(PROCESSSIZE);
  noisefilter.process(PROCESSSIZE);
  
  auto noise = noisefilter.get_output_array(0);
  auto std = (std::accumulate(noise, noise + PROCESSSIZE, 0., [](double a, double b) {return a + b*b;}) / PROCESSSIZE);
  ASSERT_NEAR(std, 1. / 3, 0.05);
}
