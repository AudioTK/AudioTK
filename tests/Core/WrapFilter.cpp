/**
 * \file WrapFilter.cpp
 */

#include <cstdint>

#include <ATK/Core/PipelineGlobalSinkFilter.h>
#include <ATK/Core/WrapFilter.h>

#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Mock/TriangleGeneratorFilter.h>

#include <gtest/gtest.h>

constexpr gsl::index PROCESSSIZE = (1024 * 1024);

TEST(WrapFilter, 2sinks_first_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<int64_t> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_amplitude(1000000);
  checker1.set_frequency(1000);

  ATK::TriangleCheckerFilter<int64_t> checker2;
  checker2.set_input_sampling_rate(48000);
  checker2.set_amplitude(1000000);
  checker2.set_frequency(1000);

  ATK::WrapFilter<int64_t> wrap(2,
      2,
      [](std::vector<ATK::InPointerFilter<int64_t>>& inputFilters,
          std::vector<ATK::OutPointerFilter<int64_t>>& outputFilters,
          std::vector<gsl::unique_ptr<ATK::BaseFilter>>& filters) {
        outputFilters[0].set_input_port(0, &inputFilters[0], 0);
        outputFilters[1].set_input_port(0, &inputFilters[1], 0);
      });
  wrap.set_input_sampling_rate(48000);
  wrap.full_setup();
  wrap.set_input_port(0, &generator, 0);
  wrap.set_input_port(1, &generator, 0);
  checker1.set_input_port(0, &wrap, 0);
  checker2.set_input_port(0, &wrap, 1);

  ATK::PipelineGlobalSinkFilter globalsink;
  globalsink.set_input_sampling_rate(48000);
  globalsink.add_filter(&checker1);
  globalsink.add_filter(&checker2);
  globalsink.process(PROCESSSIZE);
}

TEST(WrapFilter, 2sinks_second_test)
{
  ATK::TriangleGeneratorFilter<int64_t> generator;
  generator.set_output_sampling_rate(48000);
  generator.set_amplitude(1000000);
  generator.set_frequency(1000);

  ATK::TriangleCheckerFilter<int64_t> checker1;
  checker1.set_input_sampling_rate(48000);
  checker1.set_amplitude(1000000);
  checker1.set_frequency(1000);

  ATK::TriangleCheckerFilter<int64_t> checker2;
  checker2.set_input_sampling_rate(48000);
  checker2.set_amplitude(1000000);
  checker2.set_frequency(1000);

  ATK::WrapFilter<int64_t> wrap(1,
      2,
      [](std::vector<ATK::InPointerFilter<int64_t>>& inputFilters,
          std::vector<ATK::OutPointerFilter<int64_t>>& outputFilters,
          std::vector<gsl::unique_ptr<ATK::BaseFilter>>& filters) {
        outputFilters[0].set_input_port(0, &inputFilters[0], 0);
        outputFilters[1].set_input_port(0, &inputFilters[0], 0);
      });
  wrap.set_input_sampling_rate(48000);
  wrap.full_setup();
  wrap.set_input_port(0, &generator, 0);
  checker1.set_input_port(0, &wrap, 0);
  checker2.set_input_port(0, &wrap, 1);

  ATK::PipelineGlobalSinkFilter globalsink;
  globalsink.set_input_sampling_rate(48000);
  globalsink.add_filter(&checker1);
  globalsink.add_filter(&checker2);
  globalsink.process(PROCESSSIZE);
}
