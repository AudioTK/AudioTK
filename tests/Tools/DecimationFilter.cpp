/**
 * \file DecimationFilter.cpp
 */

#include <ATK/Tools/DecimationFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024 * 64;

TEST(DecimationFilter, sinus_2_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::DecimationFilter<double> filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*32);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*32);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}

TEST(DecimationFilter, sinus_4_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*32*4);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::DecimationFilter<double> filter;
  filter.set_input_sampling_rate(1024*32*4);
  filter.set_output_sampling_rate(1024*32);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*32);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}

TEST(DecimationFilter, sinus_8_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*32*8);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::DecimationFilter<double> filter;
  filter.set_input_sampling_rate(1024*32*8);
  filter.set_output_sampling_rate(1024*32);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*32);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}

TEST(DecimationFilter, sinus_16_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*32*16);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::DecimationFilter<double> filter;
  filter.set_input_sampling_rate(1024*32*16);
  filter.set_output_sampling_rate(1024*32);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*32);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}
TEST(DecimationFilter, sinus_32_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*32*32);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::DecimationFilter<double> filter;
  filter.set_input_sampling_rate(1024*32*32);
  filter.set_output_sampling_rate(1024*32);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*32);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(50, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);
}
