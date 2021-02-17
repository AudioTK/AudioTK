/**
 * \ file RLSFilter.cpp
 */

#include <ATK/Adaptive/RLSFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#include <Eigen/Core>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 1024 * 64;

TEST(RLSFilter, destructor_test)
{
  ASSERT_NO_THROW(std::make_unique<ATK::RLSFilter<double>>(100));
}

TEST(RLSFilter, size_negative_test)
{
  ATK::RLSFilter<double> filter(100);
  ASSERT_THROW(filter.set_size(0), ATK::RuntimeError);
}

TEST(RLSFilter, size_set_test)
{
  ATK::RLSFilter<double> filter(100);
  filter.set_size(10);
  ASSERT_EQ(filter.get_size(), 10);
}

TEST(RLSFilter, memory_negative_test)
{
  ATK::RLSFilter<double> filter(100);
  ASSERT_THROW(filter.set_memory(0), ATK::RuntimeError);
}

TEST(RLSFilter, memory_test)
{
  ATK::RLSFilter<double> filter(100);
  filter.set_memory(0.5);
  ASSERT_EQ(filter.get_memory(), 0.5);
}

TEST(RLSFilter, memory_positive1_test)
{
  ATK::RLSFilter<double> filter(100);
  ASSERT_THROW(filter.set_memory(1), ATK::RuntimeError);
}

TEST(RLSFilter, learning_set_test)
{
  ATK::RLSFilter<double> filter(100);
  ASSERT_EQ(filter.get_learning(), true);
  filter.set_learning(false);
  ASSERT_EQ(filter.get_learning(), false);
}

TEST(RLSFilter, memory_99_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::RLSFilter<double> filter(10);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(.99);
  filter.set_learning(false);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  filter.set_input_port(0, &generator, 0);
  checker.set_input_port(0, &filter, 0);
  
  checker.process(PROCESSSIZE);

  ASSERT_NE(filter.get_w(), nullptr);
}

TEST(RLSFilter, constant_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::SimpleSinusGeneratorFilter<double> reference;
  reference.set_output_sampling_rate(48000);
  reference.set_amplitude(-1);
  reference.set_frequency(1000);

  ATK::RLSFilter<double> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(.99);
  filter.set_learning(false);
  Eigen::Matrix<double, Eigen::Dynamic, 1> w(1);
  w << 1;
  filter.set_w(w.data());

  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_output_sampling_rate(48000);
  
  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(0);
  checker.set_frequency(1000);
  
  filter.set_input_port(0, &generator, 0);
  sum.set_input_port(0, &reference, 0);
  sum.set_input_port(1, &filter, 0);
  checker.set_input_port(0, &sum, 0);
  
  filter.process(1); // to start everything, the filter is supposed to be one sample late
  checker.process(PROCESSSIZE);
}

TEST(RLSFilter, learning_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::SimpleSinusGeneratorFilter<double> reference;
  reference.set_output_sampling_rate(48000);
  reference.set_amplitude(-1);
  reference.set_frequency(1000);
  
  ATK::RLSFilter<double> filter(10);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(0.9999);
  filter.set_learning(true);
  
  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_output_sampling_rate(48000);
  
  std::array<double, PROCESSSIZE> outdata;
  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  
  filter.set_input_port(0, &generator, 0);
  sum.set_input_port(0, &reference, 0);
  sum.set_input_port(1, &filter, 0);
  output.set_input_port(0, &sum, 0);
  
  output.process(PROCESSSIZE);
  
  for(std::int64_t i = 100; i < PROCESSSIZE; ++i) // let the RLS filter start learning first
  {
    ASSERT_NEAR(std::abs(outdata[i]), 0, 0.1);
  }
}

TEST(RLSFilter, learning_training_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::SimpleSinusGeneratorFilter<double> reference;
  reference.set_output_sampling_rate(48000);
  reference.set_amplitude(-1);
  reference.set_frequency(1000);

  ATK::RLSFilter<double> filter(10);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(0.9999);
  filter.set_learning(true);

  ATK::SumFilter<double> sum;
  sum.set_input_sampling_rate(48000);
  sum.set_output_sampling_rate(48000);

  std::array<double, PROCESSSIZE> outdata;
  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);

  filter.set_input_port(0, &generator, 0);
  sum.set_input_port(0, &reference, 0);
  sum.set_input_port(1, &filter, 0);
  output.set_input_port(0, &sum, 0);

  output.process(1000);
  filter.set_learning(false);
  output.process(PROCESSSIZE - 1000);

  for (std::int64_t i = 100; i < PROCESSSIZE; ++i) // let the RLS filter start learning first
  {
    ASSERT_NEAR(std::abs(outdata[i]), 0, 0.1);
  }

}
