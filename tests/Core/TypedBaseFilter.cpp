/**
 * \file TypedBaseFilter.cpp
 */

#include <complex>
#include <cstdint>

#include <ATK/Core/TypedBaseFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>
#include <ATK/Tools/SumFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = (1024 * 1024);

TEST(TypedBaseFilter, constructor_test_int16_t)
{
  ASSERT_NO_THROW(ATK::TypedBaseFilter<std::int16_t> filter(0, 0));
}

TEST(TypedBaseFilter, constructor_test_int32_t)
{
  ASSERT_NO_THROW(ATK::TypedBaseFilter<std::int32_t> filter(0, 0));
}

TEST(TypedBaseFilter, constructor_test_int64_t)
{
  ASSERT_NO_THROW(ATK::TypedBaseFilter<int64_t> filter(0, 0));
}

TEST(TypedBaseFilter, constructor_test_float)
{
  ASSERT_NO_THROW(ATK::TypedBaseFilter<float> filter(0, 0));
}

TEST(TypedBaseFilter, constructor_test_double)
{
  ASSERT_NO_THROW(ATK::TypedBaseFilter<double> filter(0, 0));
}

TEST(TypedBaseFilter, constructor_test_complex_float)
{
  ASSERT_NO_THROW(ATK::TypedBaseFilter<std::complex<float>> filter(0, 0));
}

TEST(TypedBaseFilter, constructor_test_complex_double)
{
  ASSERT_NO_THROW(ATK::TypedBaseFilter<std::complex<double>> filter(0, 0));
}

TEST(TypedBaseFilter, check_out_sampling_rate_test)
{
  ATK::TypedBaseFilter<float> filter(0, 0);
  ASSERT_THROW(filter.process(100), std::runtime_error);
}

TEST(TypedBaseFilter, set_input_sampling_rate_test_int16_t)
{
  ATK::TypedBaseFilter<std::int16_t> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  ASSERT_EQ(filter.get_input_sampling_rate(), 44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
  ASSERT_EQ(filter.get_nb_input_ports(), 0);
  ASSERT_EQ(filter.get_nb_output_ports(), 0);
  filter.set_nb_input_ports(0);
  filter.set_nb_output_ports(0);
}

TEST(TypedBaseFilter, set_input_sampling_rate_test_int32_t)
{
  ATK::TypedBaseFilter<std::int32_t> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  ASSERT_EQ(filter.get_input_sampling_rate(), 44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
}

TEST(TypedBaseFilter, set_input_sampling_rate_test_int64_t)
{
  ATK::TypedBaseFilter<int64_t> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  ASSERT_EQ(filter.get_input_sampling_rate(), 44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
}

TEST(TypedBaseFilter, set_input_sampling_rate_test_float)
{
  ATK::TypedBaseFilter<float> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  ASSERT_EQ(filter.get_input_sampling_rate(), 44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
}

TEST(TypedBaseFilter, set_input_sampling_rate_test_double)
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  filter.set_input_sampling_rate(44100);
  ASSERT_EQ(filter.get_input_sampling_rate(), 44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
}

TEST(TypedBaseFilter, set_output_sampling_rate_test_int16_t)
{
  ATK::TypedBaseFilter<std::int16_t> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
  ASSERT_NE(filter.get_input_sampling_rate(), 44100);
}

TEST(TypedBaseFilter, set_output_sampling_rate_test_int32_t)
{
  ATK::TypedBaseFilter<std::int32_t> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
  ASSERT_NE(filter.get_input_sampling_rate(), 44100);
}

TEST(TypedBaseFilter, set_output_sampling_rate_test_int64_t)
{
  ATK::TypedBaseFilter<int64_t> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
  ASSERT_NE(filter.get_input_sampling_rate(), 44100);
}

TEST(TypedBaseFilter, set_output_sampling_rate_test_float)
{
  ATK::TypedBaseFilter<float> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
  ASSERT_NE(filter.get_input_sampling_rate(), 44100);
}

TEST(TypedBaseFilter, set_output_sampling_rate_test_double)
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  filter.set_output_sampling_rate(44100);
  ASSERT_EQ(filter.get_output_sampling_rate(), 44100);
  ASSERT_NE(filter.get_input_sampling_rate(), 44100);
}

TEST(TypedBaseFilter, set_input_delay_test)
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  ASSERT_EQ(filter.get_input_delay(), 0);
  filter.set_input_delay(1);
  ASSERT_EQ(filter.get_input_delay(), 1);
}

TEST(TypedBaseFilter, set_output_delay_test)
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  ASSERT_EQ(filter.get_output_delay(), 0);
  filter.set_output_delay(1);
  ASSERT_EQ(filter.get_output_delay(), 1);
}

TEST(TypedBaseFilter, process_0_test)
{
  ATK::TypedBaseFilter<double> filter(0, 0);
  filter.process(0);
}

TEST(TypedBaseFilter, process_something_test)
{
  ATK::TypedBaseFilter<double> filter(0, 1);
  filter.set_output_sampling_rate(48000);
  filter.process(1);
  ASSERT_NE(filter.get_output_array(0), nullptr);
  ASSERT_EQ(1, filter.get_output_array_size());
}

TEST(TypedBaseFilter, pipeline64bits_dryrun_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  generator.dryrun(PROCESSSIZE);
  ASSERT_NE(generator.get_output_array(0), nullptr);
  ASSERT_EQ(PROCESSSIZE, generator.get_output_array_size());
}

TEST(TypedBaseFilter, pipeline64bits_triangle_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

TEST(TypedBaseFilter, pipeline64bits_input_delay_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  checker.set_input_delay(0);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);

  checker.set_input_delay(2);
  checker.process(PROCESSSIZE);
}

TEST(TypedBaseFilter, pipeline_no_such_input_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);

  ASSERT_THROW(checker.set_input_port(1, &generator, 0), std::runtime_error);
}

TEST(TypedBaseFilter, pipeline_no_such_output_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);

  ASSERT_THROW(checker.set_input_port(0, &generator, 1), std::runtime_error);
}

TEST(TypedBaseFilter, pipeline_bad_sampling_rate_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48001);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);

  ASSERT_THROW(checker.set_input_port(0, &generator, 0), std::runtime_error);
}

TEST(TypedBaseFilter, pipeline64bits_output_delay_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  generator.set_output_delay(0);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
  
  generator.set_output_delay(2);
  checker.process(PROCESSSIZE);
}

TEST(TypedBaseFilter, pipeline32bits_triangle_test)
{
  ATK::TriangleGeneratorFilter<std::int32_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<std::int32_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

TEST(TypedBaseFilter, pipeline64bitsfloat_triangle_test)
{
  ATK::TriangleGeneratorFilter<std::int32_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1<<30);
  generator.set_frequency(1000);
  
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(.5);
  checker.set_frequency(1000);
  
  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

TEST(TypedBaseFilter, throw_triangle_test)
{
  ATK::TriangleCheckerFilter<int64_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(1000000);
  checker.set_frequency(1000);

  ASSERT_THROW(checker.process(PROCESSSIZE), std::runtime_error);
}

TEST(TypedBaseFilter, int_connect_to_complex_test)
{
  ATK::TriangleGeneratorFilter<std::int32_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1 << 30);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<std::complex<float>> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(.5);
  checker.set_frequency(1000);

  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

TEST(TypedBaseFilter, complex_connect_to_complex_test)
{
  ATK::TriangleGeneratorFilter<std::complex<float>> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(.5);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<std::complex<float>> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(.5);
  checker.set_frequency(1000);

  checker.set_input_port(0, &generator, 0);
  checker.process(PROCESSSIZE);
}

TEST(TypedBaseFilter, complex_connect_to_int_test)
{
  ATK::TriangleGeneratorFilter<std::complex<float>> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1 << 30);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<std::int32_t> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(65536);
  checker.set_frequency(1000);

  checker.set_input_port(0, &generator, 0);
  ASSERT_THROW(checker.process(PROCESSSIZE), std::runtime_error);
}

TEST(TypedBaseFilter, latency_set_test)
{
  ATK::TriangleCheckerFilter<int64_t> checker;
  ASSERT_EQ(checker.get_latency(), 0);
  checker.set_latency(1);
  ASSERT_EQ(checker.get_latency(), 1);
}

TEST(TypedBaseFilter, global_latency_test)
{
  ATK::TriangleGeneratorFilter<std::int32_t> generator;
  ATK::TriangleCheckerFilter<float> checker;
  checker.set_input_port(0, &generator, 0);

  ASSERT_EQ(checker.get_global_latency(), 0);
  checker.set_latency(1);
  ASSERT_EQ(checker.get_global_latency(), 1);
  generator.set_latency(2);
  ASSERT_EQ(checker.get_global_latency(), 3);
}

TEST(TypedBaseFilter, global_latency_throw_test)
{
  ATK::TriangleCheckerFilter<float> checker;

  ASSERT_THROW(checker.get_global_latency(), std::runtime_error);
}

#if ATK_USE_THREADPOOL == 1
TEST(TypedBaseFilter, parallel)
{
  ATK::TriangleGeneratorFilter<double> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1);
  generator.set_frequency(1000);
  ATK::TriangleGeneratorFilter<double> generator2;
  generator2.set_output_sampling_rate(48000);
  generator2.set_amplitude(2);
  generator2.set_frequency(1000);

  ATK::SumFilter<double> sumfilter;
  sumfilter.set_input_sampling_rate(48000);
  sumfilter.set_output_sampling_rate(48000);

  ATK::TriangleCheckerFilter<double> checker;
  checker.set_input_sampling_rate(48000);
  checker.set_amplitude(3);
  checker.set_frequency(1000);

  sumfilter.set_input_port(0, &generator, 0);
  sumfilter.set_input_port(1, &generator2, 0);
  checker.set_input_port(0, &sumfilter, 0);
  checker.process_parallel(PROCESSSIZE);
}
#endif

