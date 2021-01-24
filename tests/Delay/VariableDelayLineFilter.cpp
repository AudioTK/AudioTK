/**
 * \ file VariableDelayLineFilter.cpp
 */

#include <iostream>

#include <ATK/Delay/VariableDelayLineFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#include <gtest/gtest.h>

#include <boost/math/constants/constants.hpp>

constexpr gsl::index PROCESSSIZE = 1024 * 64;

TEST(VariableDelayLineFilter, sinus_line16000_delaysinus_test)
{
  std::vector<double> data(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<double>() * (i+1.)/48000 * 1000);
  }
  std::vector<double> datadelay(PROCESSSIZE);
  for(gsl::index i = 0; i < PROCESSSIZE; ++i)
  {
    datadelay[i] = i * .25f;
  }

  ATK::InPointerFilter<double> generator(data.data(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);
  ATK::InPointerFilter<double> generatordelay(datadelay.data(), 1, PROCESSSIZE, false);
  generatordelay.set_output_sampling_rate(48000);

  std::vector<double> outdata(PROCESSSIZE);

  ATK::VariableDelayLineFilter<double> filter(20000);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generatordelay, 0);

  ATK::OutPointerFilter<double> output(outdata.data(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(1);
  output.process(49);
  output.process(51);
  output.process(PROCESSSIZE - 1 - 49 -51);
  
  for(gsl::index i = 0; i < PROCESSSIZE/4; ++i)
  {
    ASSERT_EQ(data[i * 4 - i], outdata[i * 4]);
  }
  for(gsl::index i = 0; i < PROCESSSIZE/4; ++i)
  {
    gsl::index current = 4*i+1;
    ASSERT_EQ((data[current - i] * 3 + data[current - i - 1]) / 4, outdata[current]);
  }
  for(gsl::index i = 0; i < PROCESSSIZE/4; ++i)
  {
    gsl::index current = 4*i+2;
    ASSERT_EQ((data[current - i] + data[current - i - 1]) / 2, outdata[current]);
  }
  for(gsl::index i = 0; i < PROCESSSIZE/4; ++i)
  {
    gsl::index current = 4*i+3;
    ASSERT_EQ((data[current - i] + data[current - i - 1] * 3) / 4, outdata[current]);
  }
}
