/**
 * \ file SumFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/SumFilter.h>
#include <ATK/Tools/VolumeFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024;

TEST(SumFilter, test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);
  
  ATK::SumFilter<double> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  sumfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(3);
  checker.set_frequency(1000);
  
  sumfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(1, &generator2, 0);
  checker.set_input_port(0, &sumfilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(SumFilter, VolumeFilter_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume(2);
  
  ATK::SumFilter<double> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  sumfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(3);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(1, &volumefilter, 0);
  checker.set_input_port(0, &sumfilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(SumFilter, MultipleVolumeFilter_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume(2);
  
  ATK::SumFilter<double> sumfilter(1, 3);
  sumfilter.set_input_sampling_rate(48000);
  sumfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(4);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(1, &volumefilter, 0);
  sumfilter.set_input_port(2, &generator, 0);
  checker.set_input_port(0, &sumfilter, 0);
  checker.process(PROCESSSIZE);
}
