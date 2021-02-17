/**
 * \ file ConvolutionFilter.cpp
 */

#include <ATK/config.h>

#include <ATK/Mock/TriangleGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/VolumeFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <ATK/EQ/CustomFIRFilter.h>
#include <ATK/EQ/FIRFilter.h>
#include <ATK/Special/ConvolutionFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = (2048);

// Original time (FIR time): 20s
// Split convolution: 7.4s
// fast FFT: 1s

TEST(ConvolutionFilter, ramp_test)
{
  const int impulse_size = 10000;
  const int split_size = 128;
  
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(-1);
  generator.set_frequency(1000);
  generator.process(48000/1000/4);
  
  ATK::ConvolutionFilter<double>::AlignedScalarVector impulse;
  for(int i = 1; i < impulse_size; ++i)
  {
    impulse.push_back(i / 10000.);
  }
  
  ATK::FIRFilter<ATK::CustomFIRCoefficients<double> > filter;
  filter.set_input_sampling_rate(48000);
  filter.set_coefficients_in(std::vector<double>(impulse.rbegin(), impulse.rend()));

  ATK::ConvolutionFilter<double> convolution;
  convolution.set_input_sampling_rate(48000);
  convolution.set_split_size(split_size);
  convolution.set_impulse(std::move(impulse));

  ATK::VolumeFilter<double> gainfilter;
  gainfilter.set_input_sampling_rate(48000);
  gainfilter.set_volume(-1);

  ATK::SumFilter<double> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);

  filter.set_input_port(0, &generator, 0);
  convolution.set_input_port(0, &generator, 0);

  gainfilter.set_input_port(0, &filter, 0);

  sumfilter.set_input_port(0, &convolution, 0);
  sumfilter.set_input_port(1, &gainfilter, 0);
  
  checker.set_input_port(0, &sumfilter, 0);

  for(int i= 1; i < PROCESSSIZE; ++i)
    checker.process(i);
}
