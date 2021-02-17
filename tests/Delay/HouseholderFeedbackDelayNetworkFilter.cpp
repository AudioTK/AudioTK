/**
 * \ file HouseholderFeedbackDelayNetworkFilter.cpp
 */

#include <ATK/Delay/FeedbackDelayNetworkFilter.h>
#include <ATK/Delay/HouseholderMixture.h>

#ifndef EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT

#include <array>
#include <fstream>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#  include <gtest/gtest.h>

#  include <boost/math/constants/constants.hpp>

const std::size_t PROCESSSIZE = 1024*64;

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_linel100_delay50_test)
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::vector<double> outdata(PROCESSSIZE);

  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_ingain(0, 1);
  filter.set_outgain(0, 1);
  
  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);
  
  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);
  
  for(gsl::index i = 0; i < 50; ++i)
  {
    ASSERT_EQ(0, outdata[i]);
  }
  
  for(gsl::index i = 50; i < PROCESSSIZE; ++i)
  {
    ASSERT_EQ(data[i - 50], outdata[i]);
  }
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_line100_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);
  
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_ingain(0, 1);
  filter.set_outgain(0, 1);
  filter.process(50);
  
  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);
  
  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);
  
  for (std::size_t i = 1; i < 100; ++i)
  {
    output.process(i);
  }
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_line1000_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);
  
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(1000);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(0, 50);
  filter.set_ingain(0, 1);
  filter.set_outgain(0, 1);
  filter.process(50);
  
  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);
  
  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);
  
  for (std::size_t i = 50; i < 1000; ++i)
  {
    output.process(i);
  }
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_liner100_delay50_test)
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  
  std::vector<double> outdata(PROCESSSIZE);

  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_ingain(1, 1);
  filter.set_outgain(1, 1);
  
  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);
  
  output.process(49);
  output.process(1);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);
  
  for(gsl::index i = 0; i < 50; ++i)
  {
    ASSERT_EQ(0, outdata[i]);
  }
  
  for(gsl::index i = 50; i < PROCESSSIZE; ++i)
  {
    ASSERT_EQ(data[i - 50], outdata[i]);
  }
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_liner100_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);
  
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_ingain(1, 1);
  filter.set_outgain(1, 1);
  filter.process(50);
  
  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);
  
  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);
  
  for (std::size_t i = 1; i < 100; ++i)
  {
    output.process(i);
  }
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_liner1000_delay50_progressive_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_frequency(480);
  
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(1000);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(1, 50);
  filter.set_ingain(1, 1);
  filter.set_outgain(1, 1);
  filter.process(50);
  
  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_input_port(0, &filter, 0);
  sum.set_input_port(1, &generator, 0);
  
  ATK::TriangleCheckerFilter<double> output;
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &sum, 0);
  output.set_amplitude(0);
  
  for (std::size_t i = 50; i < 1000; ++i)
  {
    output.process(i);
  }
}

const std::size_t OTHERPROCESSSIZE = 9600;

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_complex_test)
{
  std::vector<double> data(OTHERPROCESSSIZE);
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input_hadamard.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(data.data()), OTHERPROCESSSIZE * sizeof(double));
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, OTHERPROCESSSIZE, false);
  generator.set_output_sampling_rate(96000);

  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 4>> filter(100000);
  filter.set_input_sampling_rate(96000);
  filter.set_input_port(0, &generator, 0);
  filter.set_delay(0, 4800);
  filter.set_delay(1, 3600);
  filter.set_delay(2, 2400);
  filter.set_delay(3, 1200);
  filter.set_ingain(0, 1);
  filter.set_ingain(1, .2);
  filter.set_ingain(2, 1);
  filter.set_ingain(3, 1);
  filter.set_outgain(0, 1);
  filter.set_outgain(1, 1);
  filter.set_outgain(2, 1);
  filter.set_outgain(3, .5);
  filter.set_feedback(0, .2);
  filter.set_feedback(1, .8);
  filter.set_feedback(2, .4);
  filter.set_feedback(3, .2);

  filter.process(OTHERPROCESSSIZE);

  std::vector<double> outdata(OTHERPROCESSSIZE);
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/output_householder.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(outdata.data()), OTHERPROCESSSIZE * sizeof(double));
  }

  for (unsigned int i = 0; i < OTHERPROCESSSIZE; ++i)
  {
    ASSERT_NEAR(outdata[i], filter.get_output_array(0)[i], 0.0001);
  }
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_delay_test)
{
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(128);
  filter.set_delay(0, 10);
  ASSERT_EQ(filter.get_delay(0), 10);
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_delay_range_test)
{
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(128);
  ASSERT_THROW(filter.set_delay(0, 0), ATK::RuntimeError);
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_delay_range2_test)
{
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(128);
  ASSERT_THROW(filter.set_delay(0, 128), ATK::RuntimeError);
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_ingain_test)
{
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(128);
  filter.set_ingain(0, 0.5);
  ASSERT_EQ(filter.get_ingain(0), 0.5);
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_outgain_test)
{
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(128);
  filter.set_outgain(0, 0.5);
  ASSERT_EQ(filter.get_outgain(0), 0.5);
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_feedback_test)
{
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(128);
  filter.set_feedback(0, 0.5);
  ASSERT_EQ(filter.get_feedback(0), 0.5);
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_feedback_range_test)
{
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(128);
  ASSERT_THROW(filter.set_feedback(0, 2), ATK::RuntimeError);
}

TEST(HouseholderFeedbackDelayNetworkFilter, sinus_feedback_range2_test)
{
  ATK::FeedbackDelayNetworkFilter<ATK::HouseholderMixture<double, 2>> filter(128);
  ASSERT_THROW(filter.set_feedback(0, -2), ATK::RuntimeError);
}

#endif
