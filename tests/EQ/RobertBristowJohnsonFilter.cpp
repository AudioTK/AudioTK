/**
 * \ file RobertBristowJohnsonFilter.cpp
 */

#include <ATK/EQ/RobertBristowJohnsonFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024*64;

TEST(IIRFilter, RobertBristowJohnsonLowPassCoefficients_Q_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<double> > filter;
  filter.set_Q(20);
  ASSERT_EQ(filter.get_Q(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonLowPassCoefficients_Q_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonHighPassCoefficients_Q_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<double> > filter;
  filter.set_Q(20);
  ASSERT_EQ(filter.get_Q(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonHighPassCoefficients_Q_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassCoefficients_Q_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassCoefficients<double> > filter;
  filter.set_Q(20);
  ASSERT_EQ(filter.get_Q(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassCoefficients_Q_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassCoefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonBandPass2Coefficients_Q_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPass2Coefficients<double> > filter;
  filter.set_Q(20);
  ASSERT_EQ(filter.get_Q(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonBandPass2Coefficients_Q_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPass2Coefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonBandStopCoefficients_Q_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandStopCoefficients<double> > filter;
  filter.set_Q(20);
  ASSERT_EQ(filter.get_Q(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonBandStopCoefficients_Q_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandStopCoefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonAllPassCoefficients_Q_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonAllPassCoefficients<double> > filter;
  filter.set_Q(20);
  ASSERT_EQ(filter.get_Q(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonAllPassCoefficients_Q_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonAllPassCoefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassPeakCoefficients_Q_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<double> > filter;
  filter.set_Q(20);
  ASSERT_EQ(filter.get_Q(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassPeakCoefficients_Q_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassPeakCoefficients_gain_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<double> > filter;
  filter.set_gain(20);
  ASSERT_EQ(filter.get_gain(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassPeakCoefficients_gain_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<double> > filter;
  ASSERT_THROW(filter.set_gain(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonLowShelvingCoefficients_Q_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<double> > filter;
  filter.set_Q(20);
  ASSERT_EQ(filter.get_Q(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonLowShelvingCoefficients_Q_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonLowShelvingCoefficients_gain_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<double> > filter;
  filter.set_gain(20);
  ASSERT_EQ(filter.get_gain(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonLowShelvingCoefficients_gain_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<double> > filter;
  ASSERT_THROW(filter.set_gain(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonHighShelvingCoefficients_Q_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<double> > filter;
  filter.set_Q(20);
  ASSERT_EQ(filter.get_Q(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonHighShelvingCoefficients_Q_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<double> > filter;
  ASSERT_THROW(filter.set_Q(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonHighShelvingCoefficients_gain_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<double> > filter;
  filter.set_gain(20);
  ASSERT_EQ(filter.get_gain(), 20);
}

TEST(IIRFilter, RobertBristowJohnsonHighShelvingCoefficients_gain_range_test)
{
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<double> > filter;
  ASSERT_THROW(filter.set_gain(0), std::out_of_range);
}

TEST(IIRFilter, RobertBristowJohnsonLowPassCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.10017263357405178));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonLowPassCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1.));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonLowPassCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.04987802660970978));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonLowPassCoefficients_200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 0.5266273548331198));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonHighPassCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.0024866672050896));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonHighPassCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1.));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonHighPassCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 1.0006206013284984));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonHighPassCoefficients_200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 1.0532789138212624));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.3168938774681514));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1.));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);

  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.22340318032490636));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandPass2Coefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPass2Coefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.3168938774681514));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandPass2Coefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPass2Coefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1.));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandPass2Coefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);

  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPass2Coefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.22340318032490636));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandStopCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.9974692784275677));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024 * 64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandStopCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 6.701459011526403e-07));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024 * 64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandStopCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonBandStopCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 0.9993766908751316));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024 * 64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonAllPassCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::IIRFilter<ATK::RobertBristowJohnsonAllPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(.1);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonAllPassCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  ATK::IIRFilter<ATK::RobertBristowJohnsonAllPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(.1);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 1));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonAllPassCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);

  ATK::IIRFilter<ATK::RobertBristowJohnsonAllPassCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(.1);
  filter.set_cut_frequency(100);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 1));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassPeakCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);

  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);
  filter.set_gain(2);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.0093931154905567));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassPeakCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(100);

  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);
  filter.set_gain(2);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 2.));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonBandPassPeakCoefficients_2k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024 * 64);
  generator.set_amplitude(1);
  generator.set_frequency(2000);

  ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024 * 64);
  filter.set_output_sampling_rate(1024 * 64);
  filter.set_Q(1);
  filter.set_cut_frequency(100);
  filter.set_gain(2);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024 * 64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(2000, 1.0018333926095173));
  checker.set_checks(frequency_checks);

  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);

  filter.process(1024 * 64);

  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonLowShelvingCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_gain(.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.0037031041980957));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonLowShelvingCoefficients_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_gain(.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(10, 0));
  frequency_checks.push_back(std::make_pair(100, 0.7071067811865296));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonLowShelvingCoefficients_200_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(200);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(100);
  filter.set_gain(.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(200, 1.0439000773319405));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonHighShelvingCoefficients_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(1000);
  filter.set_gain(.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.7071067811865515));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonHighShelvingCoefficients_10k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(1000);
  filter.set_gain(.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.4984228523764117));
  frequency_checks.push_back(std::make_pair(1000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, RobertBristowJohnsonHighShelvingCoefficients_500_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(1024*64);
  generator.set_amplitude(1);
  generator.set_frequency(500);
  
  ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<double> > filter;
  filter.set_input_sampling_rate(1024*64);
  filter.set_output_sampling_rate(1024*64);
  filter.set_cut_frequency(1000);
  filter.set_gain(.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(1024*64);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(500, 1.0439302711974656));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}
