/**
 * \ file VolumeFilter.cpp
 */

#include <cmath>

#include <ATK/Tools/VolumeFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024;

TEST(VolumeFilter, volume_test)
{
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_volume(10);
  ASSERT_EQ(volumefilter.get_volume(), 10);
}

TEST(VolumeFilter, 1_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(VolumeFilter, 0dB_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume_db(0);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(VolumeFilter, 2_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume(2);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(2);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(VolumeFilter, 6dB_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume_db(6);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1.995262);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(VolumeFilter, 0_5_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume(.5);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(.5);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(VolumeFilter, _6dB_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::VolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_volume_db(-6);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1/1.995262);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &volumefilter, 0);
  checker.process(PROCESSSIZE);
}
