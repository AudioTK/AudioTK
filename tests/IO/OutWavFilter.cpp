/**
 * \ file OutWavFilter.cpp
 */

#include <ATK/IO/InWavFilter.h>
#include <ATK/IO/OutWavFilter.h>

#include <ATK/config.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = (1024);

TEST(OutWavFilter, OutFloat_1k_test)
{
  {// setup
    ATK::SimpleSinusGeneratorFilter<float> generator;
    generator.set_input_sampling_rate(48000);
    generator.set_output_sampling_rate(48000);
    generator.set_amplitude(1);
    generator.set_frequency(1000);
    
    ATK::OutWavFilter<float> filter("outsinus1k.wav");
    filter.set_input_sampling_rate(48000);
    filter.set_output_sampling_rate(48000);
    filter.set_nb_input_ports(1);
    filter.set_input_port(0, &generator, 0);
    
    filter.process(PROCESSSIZE);
  }
  
  ATK::SimpleSinusGeneratorFilter<float> generator;
  generator.set_input_sampling_rate(48000);
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(-1);
  generator.set_frequency(1000);
  
  ATK::InWavFilter<float> filter("outsinus1k.wav");
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  
  ATK::SumFilter<float> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  sumfilter.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_output_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  sumfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(1, &filter, 0);
  
  checker.set_input_port(0, &sumfilter, 0);
  
  checker.process(PROCESSSIZE/2);
  checker.process(PROCESSSIZE/2);
}

TEST(OutWavFilter, OutFloat_1k2k_test)
{
  {
    ATK::SimpleSinusGeneratorFilter<float> generator1k;
    generator1k.set_output_sampling_rate(48000);
    generator1k.set_amplitude(1);
    generator1k.set_frequency(1000);
    ATK::SimpleSinusGeneratorFilter<float> generator2k;
    generator2k.set_output_sampling_rate(48000);
    generator2k.set_amplitude(1);
    generator2k.set_frequency(2000);
    
    ATK::OutWavFilter<float> filter("outsinus1k2k.wav");
    filter.set_input_sampling_rate(48000);
    filter.set_nb_input_ports(2);
    filter.set_input_port(0, &generator1k, 0);
    filter.set_input_port(1, &generator2k, 0);
    
    filter.process(PROCESSSIZE);
  }
  
  ATK::SimpleSinusGeneratorFilter<float> generator1k;
  generator1k.set_output_sampling_rate(48000);
  generator1k.set_amplitude(-1);
  generator1k.set_frequency(1000);
  ATK::SimpleSinusGeneratorFilter<float> generator2k;
  generator2k.set_output_sampling_rate(48000);
  generator2k.set_amplitude(-1);
  generator2k.set_frequency(2000);
  
  ATK::InWavFilter<float> filter("outsinus1k2k.wav");
  filter.set_output_sampling_rate(48000);
  
  ATK::SumFilter<float> sumfilter1;
  sumfilter1.set_input_sampling_rate(48000);
  sumfilter1.set_input_port(0, &generator1k, 0);
  sumfilter1.set_input_port(1, &filter, 0);
  
  ATK::SumFilter<float> sumfilter2;
  sumfilter2.set_input_sampling_rate(48000);
  sumfilter2.set_input_port(0, &generator2k, 0);
  sumfilter2.set_input_port(1, &filter, 1);
  
  ATK::SumFilter<float> sumfilter3;
  sumfilter3.set_input_sampling_rate(48000);
  sumfilter3.set_input_port(0, &sumfilter1, 0);
  sumfilter3.set_input_port(1, &sumfilter2, 0);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  checker.set_input_port(0, &sumfilter3, 0);
  
  checker.process(PROCESSSIZE);
}
