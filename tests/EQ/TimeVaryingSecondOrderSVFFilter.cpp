/**
 * \ file TimeVaryingSecondOrderSVFFilter.cpp
 */

#include <ATK/Core/InPointerFilter.h>

#include <ATK/EQ/TimeVaryingSecondOrderSVFFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#include <array>

#include <boost/math/constants/constants.hpp>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024*64;
constexpr gsl::index input_sampling_rate = 1024*64;

TEST(TimeVaryingSecondOrderSVFBandPassCoefficients, Q_test)
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  filter.set_Q(0.5);
  ASSERT_EQ(filter.get_Q(), 0.5);
}

TEST(TimeVaryingSecondOrderSVFBandPassCoefficients, Q_range_test)
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0.), std::out_of_range);
}

TEST(TimeVaryingSecondOrderSVFBellCoefficients, gain_test)
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_gain(0.5);
  ASSERT_EQ(filter.get_gain(), 0.5);
}

TEST(TimeVaryingSecondOrderSVFBellCoefficients, gain_range_test)
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  ASSERT_THROW(filter.set_gain(0.), std::out_of_range);
}

TEST(TimeVaryingSecondOrderSVFLowShelfCoefficients, Q_test)
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double> > filter;
  filter.set_gain(0.5);
  ASSERT_EQ(filter.get_gain(), 0.5);
}

TEST(TimeVaryingSecondOrderSVFHighShelfCoefficients, Q_test)
{
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double> > filter;
  filter.set_gain(0.5);
  ASSERT_EQ(filter.get_gain(), 0.5);
}

TEST(TimeVaryingSecondOrderSVFBandPassCoefficients, 1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_Q(1);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.3168938774681514));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFBandPassCoefficients, 100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_Q(1);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFBandPassCoefficients, 2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_Q(1);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.22340318032490636));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFLowPassCoefficients, 1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.10017263357405178));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFLowPassCoefficients, 100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFLowPassCoefficients, 2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.04987802660970978));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFLowPassCoefficients, 200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.5266273548331198));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFHighPassCoefficients, 1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.0024866672050896));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFHighPassCoefficients, 100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFHighPassCoefficients, 2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 1.0006206013284984));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFHighPassCoefficients, 200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 1.0532789138212624));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFNotchCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.997469278));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFNotchCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 2.43511333e-04));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFNotchCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.999376691));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFNotchCoefficients_200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.912173284));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFPeakCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.98735801));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFPeakCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1.41421356));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFPeakCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.99688421));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFPeakCoefficients_200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.52667576));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFBellCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(10);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.19195065));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFBellCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(10);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 10));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFBellCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(10);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 1.05730389));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFFilter, SVFBellCoefficients_200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(10);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 2.59346645));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFLowShelvingCoefficients, 1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.0018539205036439));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);

  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFLowShelvingCoefficients, 100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.949414461057972));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFLowShelvingCoefficients, 200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);

  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 100 / input_sampling_rate);;
  }

  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 1.037173648834839));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);

  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFHighShelvingCoefficients, 1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 1000 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.7905890936892349));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFHighShelvingCoefficients, 10k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 1000 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.5062960600823273));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(TimeVaryingSecondOrderSVFHighShelvingCoefficients, 500_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(500);
  
  ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_gain(.5);
  
  std::array<float, 2*PROCESSSIZE> data;
  for(gsl::index i = 0; i < 2*PROCESSSIZE; ++i)
  {
    data[i] = std::tan(boost::math::constants::pi<double>() * 1000 / input_sampling_rate);;
  }
  
  ATK::InPointerFilter<float> generator2(data.data(), 1, 2*PROCESSSIZE, false);
  generator2.set_output_sampling_rate(1024*64);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(500, 0.9220383944187385));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator2, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}
