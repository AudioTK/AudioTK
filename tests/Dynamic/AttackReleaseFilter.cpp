/**
 * \ file AttackReleaseFilter.cpp
 */

#include <ATK/Dynamic/AttackReleaseFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 1024*64;

TEST(AttackRelease, attack_test)
{
  ATK::AttackReleaseFilter<double> filter;
  filter.set_attack(0.5);
  ASSERT_EQ(filter.get_attack(), 0.5);
}

TEST(AttackRelease, attack_range_test)
{
  ATK::AttackReleaseFilter<double> filter;
  ASSERT_THROW(filter.set_attack(-0.000001), ATK::RuntimeError);
}

TEST(AttackRelease, attack_range2_test)
{
  ATK::AttackReleaseFilter<double> filter;
  ASSERT_THROW(filter.set_attack(1.000001), ATK::RuntimeError);
}

TEST(AttackRelease, release_test)
{
  ATK::AttackReleaseFilter<double> filter;
  filter.set_release(0.5);
  ASSERT_EQ(filter.get_release(), 0.5);
}

TEST(AttackRelease, release_range_test)
{
  ATK::AttackReleaseFilter<double> filter;
  ASSERT_THROW(filter.set_release(-0.000001), ATK::RuntimeError);
}

TEST(AttackRelease, release_range2_test)
{
  ATK::AttackReleaseFilter<double> filter;
  ASSERT_THROW(filter.set_release(1.000001), ATK::RuntimeError);
}

TEST(AttackReleaseFilter, triangle_test)
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE/2; ++i)
  {
    data[i] = i / 48000;
  }
  for(gsl::index i = 0; i < PROCESSSIZE/2; ++i)
  {
    data[PROCESSSIZE/2 + i] = (PROCESSSIZE/2 - i) / 48000;
  }
  
  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::AttackReleaseFilter<double> filter(1);
  filter.set_attack(std::exp(-1./(48000 * 1e-3)));
  filter.set_release(std::exp(-1./(48000 * 100e-3)));
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(gsl::index i = 0; i < PROCESSSIZE/2; ++i)
  {
    ASSERT_GE(data[i], outdata[i]);
  }
  for(gsl::index i = 0; i < PROCESSSIZE/2; ++i)
  {
    ASSERT_GE(outdata[PROCESSSIZE / 2 + i], outdata[PROCESSSIZE / 2 + i - 1]);
  }
}
