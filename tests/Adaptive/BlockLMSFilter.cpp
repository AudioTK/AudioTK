/**
 * \ file BlockLMSFilter.cpp
 */

#include <array>
#include <fstream>
#include <iostream>

#include <ATK/Adaptive/BlockLMSFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
#include <ATK/Mock/TriangleCheckerFilter.h>

#include <ATK/Tools/SumFilter.h>

#include <Eigen/Core>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 1200;

TEST(BlockLMSFilter, destructor_test)
{
  ASSERT_NO_THROW(std::make_unique<ATK::BlockLMSFilter<double>>(100));
}

TEST(BlockLMSFilter, size_negative_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_size(0), ATK::RuntimeError);
}

TEST(BlockLMSFilter, size_set_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  filter.set_size(10);
  ASSERT_EQ(filter.get_size(), 10);
}

TEST(BlockLMSFilter, build_throw_test)
{
  ASSERT_THROW(ATK::BlockLMSFilter<double> filter(0), ATK::RuntimeError);
}

TEST(BlockLMSFilter, blocksize_negative_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_block_size(0), ATK::RuntimeError);
}

TEST(BlockLMSFilter, blocksize_set_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  filter.set_block_size(10);
  ASSERT_EQ(filter.get_block_size(), 10);
}

TEST(BlockLMSFilter, memory_negative_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_memory(0), ATK::RuntimeError);
}

TEST(BlockLMSFilter, memory_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  filter.set_memory(0.5);
  ASSERT_EQ(filter.get_memory(), 0.5);
}

TEST(BlockLMSFilter, memory_positive1_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_memory(1), ATK::RuntimeError);
}

TEST(BlockLMSFilter, mu_negative_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_mu(0), ATK::RuntimeError);
}

TEST(BlockLMSFilter, mu_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  filter.set_mu(0.5);
  ASSERT_EQ(filter.get_mu(), 0.5);
}

TEST(BlockLMSFilter, mu_positive1_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_mu(1), ATK::RuntimeError);
}

TEST(BlockLMSFilter, learning_set_test)
{
  ATK::BlockLMSFilter<double> filter(100);
  ASSERT_EQ(filter.get_learning(), true);
  filter.set_learning(false);
  ASSERT_EQ(filter.get_learning(), false);
}

TEST(BlockLMSFilter, memory_999_test)
{
  std::array<double, PROCESSSIZE> data;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input_lms.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(data.data()), PROCESSSIZE * sizeof(double));
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  ATK::BlockLMSFilter<double> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(.999);
  filter.set_mu(.0001);

  std::array<double, PROCESSSIZE> outdata;
  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_output_sampling_rate(48000);

  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  output.set_input_port(0, &filter, 0);

  filter.process(100);
  output.process(PROCESSSIZE);
  ASSERT_NE(filter.get_w(), nullptr);

  std::array<double, PROCESSSIZE> ref;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/output_blocklms.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(ref.data()), PROCESSSIZE * sizeof(double));
  }

  for (unsigned int i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(outdata[i], ref[i], 0.0001);
  }
}
