/**
 * \ file RemezBasedFilter.cpp
 */

#include <ATK/EQ/FIRFilter.h>
#include <ATK/EQ/RemezBasedFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = (1024 * 64);

TEST(FIRFilter, Remez_bad_template_test)
{
  ATK::FIRFilter<ATK::RemezBasedCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_order(12);
  std::vector<std::pair<std::pair<double, double>, std::pair<double, double>> > target;
  target.push_back(std::make_pair(std::make_pair(0, 0.4), std::make_pair(1, 1)));
  target.push_back(std::make_pair(std::make_pair(0, 1), std::make_pair(0, 2)));

  ASSERT_THROW(filter.set_template(target), std::runtime_error);
}

TEST(FIRFilter, Remez_even_order_test)
{
  ATK::FIRFilter<ATK::RemezBasedCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  std::vector<std::pair<std::pair<double, double>, std::pair<double, double>> > target;
  target.push_back(std::make_pair(std::make_pair(0, 0.4), std::make_pair(1, 1)));
  target.push_back(std::make_pair(std::make_pair(0.5, 1), std::make_pair(0, 2)));
  filter.set_template(target);

  ASSERT_THROW(filter.set_order(13), std::runtime_error);
}

TEST(FIRFilter, Remez_LowPassCoefficients_16k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::FIRFilter<ATK::RemezBasedCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_order(12);
  std::vector<std::pair<std::pair<double, double>, std::pair<double, double>> > target;
  target.push_back(std::make_pair(std::make_pair(0, 0.4), std::make_pair(1, 1)));
  target.push_back(std::make_pair(std::make_pair(0.5, 1), std::make_pair(0, 2)));
  filter.set_template(target);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.0680341));
  frequency_checks.push_back(std::make_pair(2000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}
