/**
 * \ file SD1ToneFilter.cpp
 */

#include <ATK/EQ/PedalToneStackFilter.h>
#include <ATK/EQ/IIRFilter.h>

#include <ATK/Mock/FFTCheckerFilter.h>
#include <ATK/Mock/SimpleSinusGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = 1024*1026;
constexpr gsl::index SAMPLINGRATE = 1024*64;

TEST(IIRFilter, SD1ToneCoefficients_tone_test)
{
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_tone(.5);
  ASSERT_EQ(filter.get_tone(), .5);
}

TEST(IIRFilter, SD1ToneCoefficients_throw_1_test)
{
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  ASSERT_THROW(filter.set_tone(1.001), std::out_of_range);
}

TEST(IIRFilter, SD1ToneCoefficients_throw_0_test)
{
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  ASSERT_THROW(filter.set_tone(-0.001), std::out_of_range);
}

TEST(IIRFilter, SD1ToneCoefficients_alpha0_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.9813101780535352));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, SD1ToneCoefficients_alpha0_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.6236407269569778));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, SD1ToneCoefficients_alpha0_10k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.525581554888129));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, SD1ToneCoefficients_alpha1_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(1);

  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 1.0106781785286139));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, SD1ToneCoefficients_alpha1_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(1);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 1.3065626075847556));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, SD1ToneCoefficients_alpha1_10k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(1);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 1.2770732276129428));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, SD1ToneCoefficients_alpha05_100_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(100);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0.99588245799196));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, SD1ToneCoefficients_alpha05_1k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0.9164270318538241));
  frequency_checks.push_back(std::make_pair(10000, 0));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}

TEST(IIRFilter, SD1ToneCoefficients_alpha05_10k_test)
{
  ATK::SimpleSinusGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(SAMPLINGRATE);
  generator.set_amplitude(1);
  generator.set_frequency(10000);
  
  ATK::IIRFilter<ATK::SD1ToneCoefficients<double> > filter;
  filter.set_input_sampling_rate(SAMPLINGRATE);
  filter.set_output_sampling_rate(SAMPLINGRATE);
  filter.set_tone(0.5);
  
  ATK::FFTCheckerFilter<double> checker;
  checker.set_input_sampling_rate(SAMPLINGRATE);
  std::vector<std::pair<int, double> > frequency_checks;
  frequency_checks.push_back(std::make_pair(100, 0));
  frequency_checks.push_back(std::make_pair(1000, 0));
  frequency_checks.push_back(std::make_pair(10000, 0.7559110473244306));
  checker.set_checks(frequency_checks);
  
  checker.set_input_port(0, &filter, 0);
  filter.set_input_port(0, &generator, 0);
  
  filter.process(1024*64);
  
  checker.process(PROCESSSIZE);
}
