/**
 * \ file OffsetVolumeFilter.cpp
 */

#include <cmath>

#include <ATK/Core/InPointerFilter.h>

#include <ATK/Tools/OffsetVolumeFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#include <array>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024;

TEST(OffsetVolumeFilter, volume_test)
{
  ATK::OffsetVolumeFilter<double> volumefilter;
  volumefilter.set_volume(10);
  ASSERT_EQ(volumefilter.get_volume(), 10);
}

TEST(OffsetVolumeFilter, offset_test)
{
  ATK::OffsetVolumeFilter<double> volumefilter;
  volumefilter.set_offset(10);
  ASSERT_EQ(volumefilter.get_offset(), 10);
}

TEST(OffsetVolumeFilter, 1_0_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::OffsetVolumeFilter<double> volumefilter;
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

TEST(OffsetVolumeFilter, 1_1_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::OffsetVolumeFilter<double> volumefilter;
  volumefilter.set_input_sampling_rate(48000);
  volumefilter.set_output_sampling_rate(48000);
  volumefilter.set_offset(1);

  std::array<float, PROCESSSIZE> data;
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = -1;
  }

  ATK::InPointerFilter<float> constantfilter(data.data(), 1, PROCESSSIZE, false);
  constantfilter.set_output_sampling_rate(48000);
  
  ATK::SumFilter<float> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  sumfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1);
  checker.set_frequency(1000);
  
  volumefilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(0, &volumefilter, 0);
  sumfilter.set_input_port(1, &constantfilter, 0);
  checker.set_input_port(0, &sumfilter, 0);
  checker.process(PROCESSSIZE);
}

TEST(OffsetVolumeFilter, 2_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::OffsetVolumeFilter<double> volumefilter;
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

TEST(OffsetVolumeFilter, 0_5_test)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::OffsetVolumeFilter<double> volumefilter;
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
