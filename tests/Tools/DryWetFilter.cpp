/**
 * \ file DryWetFilter.cpp
 */

#include <cmath>

#include <ATK/Core/InPointerFilter.h>

#include <ATK/Tools/DryWetFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024;

TEST(DryWetFilter, drywet_set_test)
{
  ATK::DryWetFilter<double> filter;
  filter.set_dry(0.5);
  ASSERT_EQ(filter.get_dry(), 0.5);
}

TEST(DryWetFilter, drywet_range_test)
{
  ATK::DryWetFilter<double> filter;
  ASSERT_THROW(filter.set_dry(-0.00001), std::out_of_range);
}

TEST(DryWetFilter, drywet_range2_test)
{
  ATK::DryWetFilter<double> filter;
  ASSERT_THROW(filter.set_dry(1.00001), std::out_of_range);
}

TEST(DryWetFilter, 1_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::DryWetFilter<double> drywetfilter;
  drywetfilter.set_input_sampling_rate(48000);
  drywetfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  drywetfilter.set_input_port(0, &generator, 0);
  drywetfilter.set_input_port(1, &generator, 0);
  checker.set_input_port(0, &drywetfilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(DryWetFilter, 0_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::DryWetFilter<double> drywetfilter;
  drywetfilter.set_input_sampling_rate(48000);
  drywetfilter.set_output_sampling_rate(48000);
  drywetfilter.set_dry(0);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  drywetfilter.set_input_port(0, &generator, 0);
  drywetfilter.set_input_port(1, &generator, 0);
  checker.set_input_port(0, &drywetfilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(DryWetFilter, 0_5_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::DryWetFilter<double> drywetfilter;
  drywetfilter.set_input_sampling_rate(48000);
  drywetfilter.set_output_sampling_rate(48000);
  drywetfilter.set_dry(.5);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  drywetfilter.set_input_port(0, &generator, 0);
  drywetfilter.set_input_port(1, &generator, 0);
  checker.set_input_port(0, &drywetfilter, 0);
  checker.process(PROCESSSIZE);
}
