/**
 * \file PipelineGlobalSinkFilter.cpp
 */

#include <cstdint>

#include <ATK/Core/PipelineGlobalSinkFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = (1024 * 1024);

TEST(PipelineGlobalSinkFilter, constructor_test)
{
  ASSERT_NO_THROW(ATK::PipelineGlobalSinkFilter filter);
}

TEST(PipelineGlobalSinkFilter, check_remove_inexisting_test)
{
  ATK::TriangleCheckerFilter<int64_t> checker;
  
  ATK::PipelineGlobalSinkFilter globalsink;

  ASSERT_THROW(globalsink.remove_filter(&checker), std::runtime_error);
}

TEST(PipelineGlobalSinkFilter, check_remove_existing_test)
{
  ATK::TriangleCheckerFilter<int64_t> checker;
  
  ATK::PipelineGlobalSinkFilter globalsink;
  ASSERT_NO_THROW(globalsink.add_filter(&checker));
  ASSERT_THROW(globalsink.add_filter(&checker), std::runtime_error);

  ASSERT_NO_THROW(globalsink.remove_filter(&checker));
  ASSERT_THROW(globalsink.remove_filter(&checker), std::runtime_error);
}

TEST(PipelineGlobalSinkFilter, 2sinks_first_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<int64_t> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_amplitude(1000000);
  checker1.set_frequency(1000);
  checker1.set_input_port(0, &generator, 0);

  ATK::TriangleCheckerFilter<int64_t> checker2;
  checker2.set_input_sampling_rate(48000);
  checker2.set_amplitude(1000000);
  checker2.set_frequency(1000);
  checker2.set_input_port(0, &generator, 0);

  ATK::PipelineGlobalSinkFilter globalsink;
  globalsink.set_input_sampling_rate(48000);
  globalsink.add_filter(&checker1);
  globalsink.add_filter(&checker2);
  globalsink.process(PROCESSSIZE);
  checker1.process(PROCESSSIZE);
}

TEST(PipelineGlobalSinkFilter, 2sinks_second_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<int64_t> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_amplitude(1000000);
  checker1.set_frequency(1000);
  checker1.set_input_port(0, &generator, 0);

  ATK::TriangleCheckerFilter<int64_t> checker2;
  checker2.set_input_sampling_rate(48000);
  checker2.set_amplitude(1000000);
  checker2.set_frequency(1000);
  checker2.set_input_port(0, &generator, 0);

  ATK::PipelineGlobalSinkFilter globalsink;
  globalsink.set_input_sampling_rate(48000);
  globalsink.add_filter(&checker1);
  globalsink.add_filter(&checker2);
  globalsink.process(PROCESSSIZE);
  checker2.process(PROCESSSIZE);
}

TEST(PipelineGlobalSinkFilter, no_set_input_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);
  
  ATK::PipelineGlobalSinkFilter globalsink;
  ASSERT_THROW(globalsink.set_input_port(0, &generator, 0), std::runtime_error);
}
