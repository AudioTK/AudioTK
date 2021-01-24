/**
 * \ file LMSFilter.cpp
 */

#include <array>
#include <fstream>

#include <ATK/Adaptive/LMSFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <ATK/Tools/SumFilter.h>

#include <Eigen/Core>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 1200;

TEST(LMSFilter, destructor_test)
{
  ASSERT_NO_THROW(std::make_unique<ATK::LMSFilter<double>>(100));
}

TEST(LMSFilter, size_negative_test)
{
  ATK::LMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_size(0), ATK::RuntimeError);
}

TEST(LMSFilter, size_set_test)
{
  ATK::LMSFilter<double> filter(100);
  filter.set_size(10);
  ASSERT_EQ(filter.get_size(), 10);
}

TEST(LMSFilter, mode_set_test)
{
  ATK::LMSFilter<double> filter(100);
  filter.set_mode(ATK::LMSFilter<double>::Mode::NORMALIZED);
  ASSERT_EQ(filter.get_mode(), ATK::LMSFilter<double>::Mode::NORMALIZED);
}

TEST(LMSFilter, memory_negative_test)
{
  ATK::LMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_memory(0), ATK::RuntimeError);
}

TEST(LMSFilter, memory_test)
{
  ATK::LMSFilter<double> filter(100);
  filter.set_memory(0.5);
  ASSERT_EQ(filter.get_memory(), 0.5);
}

TEST(LMSFilter, memory_positive1_test)
{
  ATK::LMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_memory(1), ATK::RuntimeError);
}

TEST(LMSFilter, mu_negative_test)
{
  ATK::LMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_mu(0), ATK::RuntimeError);
}

TEST(LMSFilter, mu_test)
{
  ATK::LMSFilter<double> filter(100);
  filter.set_mu(0.5);
  ASSERT_EQ(filter.get_mu(), 0.5);
}

TEST(LMSFilter, mu_positive1_test)
{
  ATK::LMSFilter<double> filter(100);
  ASSERT_THROW(filter.set_mu(1), ATK::RuntimeError);
}

TEST(LMSFilter, learning_set_test)
{
  ATK::LMSFilter<double> filter(100);
  ASSERT_EQ(filter.get_learning(), true);
  filter.set_learning(false);
  ASSERT_EQ(filter.get_learning(), false);
}

TEST(LMSFilter, memory_99_test)
{
  std::array<double, PROCESSSIZE> data;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/input_lms.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(data.data()), PROCESSSIZE * sizeof(double));
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  ATK::LMSFilter<double> filter(100);
  filter.set_input_sampling_rate(48000);
  filter.set_output_sampling_rate(48000);
  filter.set_memory(.999);
  filter.set_mu(.01);
  
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);
  
  filter.process(PROCESSSIZE);
  ASSERT_NE(filter.get_w(), nullptr);

  std::array<double, PROCESSSIZE> outdata;
  {
    std::ifstream input(ATK_SOURCE_TREE "/tests/data/output_lms.dat", std::ios::binary);
    input.read(reinterpret_cast<char*>(outdata.data()), PROCESSSIZE * sizeof(double));
  }

  for (unsigned int i = 0; i < PROCESSSIZE; ++i)
  {
    ASSERT_NEAR(outdata[i], filter.get_output_array(0)[i], 0.0001);
  }
}
