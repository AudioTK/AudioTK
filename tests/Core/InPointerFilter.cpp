/**
 * \ file InPointerFilter.cpp
 */

#include <cmath>

#include <boost/math/constants/constants.hpp>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 100;

TEST(InPointerFloat, sin1k_test)
{
  std::array<float, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  ATK::SimpleSinusGeneratorFilter<float> check;
  check.set_output_sampling_rate(48000);
  check.set_amplitude(-1);
  check.set_frequency(1000);
  
  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &generator, 0);
  sum.set_input_port(1, &check, 0);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &sum, 0);

  checker.process(2);
  checker.process(PROCESSSIZE - 2);
}

TEST(InPointerFloat, sin1k_test_set_pointer)
{
  std::array<float, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  std::array<float, PROCESSSIZE> data2;

  ATK::InPointerFilter<float> generator(data2.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  generator.set_pointer(data.data(), PROCESSSIZE);
  
  ATK::SimpleSinusGeneratorFilter<float> check;
  check.set_output_sampling_rate(48000);
  check.set_amplitude(-1);
  check.set_frequency(1000);
  
  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &generator, 0);
  sum.set_input_port(1, &check, 0);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &sum, 0);

  checker.process(2);
  checker.process(PROCESSSIZE - 2);
}

TEST(InPointerDouble, sin1k_test)
{
  std::array<double, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  ATK::SimpleSinusGeneratorFilter<double> check;
  check.set_output_sampling_rate(48000);
  check.set_amplitude(-1);
  check.set_frequency(1000);
  
  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &generator, 0);
  sum.set_input_port(1, &check, 0);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &sum, 0);
  
  checker.process(2);
  checker.process(PROCESSSIZE - 2);
}

TEST(InPointerFloat, sin1k2k_interleaved_test)
{
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[2*i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
    data[2*i+1] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 2000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), PROCESSSIZE, 2, true);
  generator.set_output_sampling_rate(48000);
  
  ATK::SimpleSinusGeneratorFilter<float> check1;
  check1.set_output_sampling_rate(48000);
  check1.set_amplitude(-1);
  check1.set_frequency(1000);
  
  ATK::SimpleSinusGeneratorFilter<float> check2;
  check2.set_output_sampling_rate(48000);
  check2.set_amplitude(-1);
  check2.set_frequency(2000);
  
  ATK::SumFilter<float> sum1;
  sum1.set_input_sampling_rate(48000);
  sum1.set_input_port(0, &generator, 0);
  sum1.set_input_port(1, &check1, 0);
  ATK::SumFilter<float> sum2;
  sum2.set_input_sampling_rate(48000);
  sum2.set_input_port(0, &generator, 1);
  sum2.set_input_port(1, &check2, 0);
  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &sum1, 0);
  sum.set_input_port(1, &sum2, 0);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &sum, 0);
  
  checker.process(2);
  checker.process(PROCESSSIZE - 2);
}

TEST(InPointerFloat, sin1k2k_noninterleaved_test)
{
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i+PROCESSSIZE] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 2000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), 2, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  ATK::SimpleSinusGeneratorFilter<float> check1;
  check1.set_output_sampling_rate(48000);
  check1.set_amplitude(-1);
  check1.set_frequency(1000);
  
  ATK::SimpleSinusGeneratorFilter<float> check2;
  check2.set_output_sampling_rate(48000);
  check2.set_amplitude(-1);
  check2.set_frequency(2000);
  
  ATK::SumFilter<float> sum1;
  sum1.set_input_sampling_rate(48000);
  sum1.set_input_port(0, &generator, 0);
  sum1.set_input_port(1, &check1, 0);
  ATK::SumFilter<float> sum2;
  sum2.set_input_sampling_rate(48000);
  sum2.set_input_port(0, &generator, 1);
  sum2.set_input_port(1, &check2, 0);
  ATK::SumFilter<float> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &sum1, 0);
  sum.set_input_port(1, &sum2, 0);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  checker.set_input_port(0, &sum, 0);
  
  checker.process(2);
  checker.process(PROCESSSIZE - 2);
}

TEST(InPointerFloat, sin1k_overflow_interleaved_test)
{
  std::array<float, 2*PROCESSSIZE> data;
  std::array<float, 2*PROCESSSIZE> output;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[2*i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
    data[2*i+1] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<float> generator(data.data(), PROCESSSIZE, 2, true);
  generator.set_output_sampling_rate(48000);
  
  ATK::OutPointerFilter<float> getter(output.data(), 1, 2 * PROCESSSIZE, false);
  getter.set_input_sampling_rate(48000);
  getter.set_output_sampling_rate(48000);
  getter.set_input_port(0, generator, 0);
  
  getter.process(PROCESSSIZE*2);
  
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_EQ(data[2 * i], output[i]);
  }
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_EQ(0, output[i + PROCESSSIZE]);
  }
}
