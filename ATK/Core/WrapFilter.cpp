/**
 * \file WrapFilter.cpp
 */

#include "WrapFilter.h"
#include <ATK/Core/Utilities.h>

#if ATK_USE_THREADPOOL == 1
#  include <tbb/task_group.h>
#endif

#include <algorithm>

namespace ATK
{
template <typename DataType_, typename DataType__>
WrapFilter<DataType_, DataType__>::WrapFilter(gsl::index nb_input_ports,
    gsl::index nb_output_ports,
    const std::function<void(std::vector<InPointerFilter<DataType_>>& inputFilters,
        std::vector<OutPointerFilter<DataType__>>& outputFilters,
        std::vector<gsl::unique_ptr<BaseFilter>>& filters)>& fun)
  : Parent(nb_input_ports, nb_output_ports)
{
  for(size_t i = 0; i < nb_input_ports; ++i)
  {
    inputFilters.emplace_back(nullptr, 1, 0, false);
  }
  for(size_t i = 0; i < nb_output_ports; ++i)
  {
    outputFilters.emplace_back(nullptr, 1, 0, false);
  }
  for(size_t i = 0; i < nb_output_ports; ++i)
  {
    sink.add_filter(&outputFilters[i]);
  }

  fun(inputFilters, outputFilters, filters);
}

template <typename DataType_, typename DataType__>
void WrapFilter<DataType_, DataType__>::full_setup()
{
  for(auto& filter: inputFilters)
  {
    filter.set_input_sampling_rate(get_input_sampling_rate());
    filter.set_output_sampling_rate(get_input_sampling_rate());
  }
  for(auto& filter: outputFilters)
  {
    filter.set_input_sampling_rate(get_output_sampling_rate());
    filter.set_output_sampling_rate(get_output_sampling_rate());
  }
  for(auto& filter: filters)
  {
    filter->set_input_sampling_rate(get_input_sampling_rate());
    filter->set_output_sampling_rate(get_output_sampling_rate());
  }
  sink.set_input_sampling_rate(get_input_sampling_rate());
  sink.set_output_sampling_rate(get_output_sampling_rate());
}

template <typename DataType_, typename DataType__>
void WrapFilter<DataType_, DataType__>::dry_run(gsl::index size)
{
  reset();
  sink.dryrun(size);
}

template <typename DataType_, typename DataType__>
void WrapFilter<DataType_, DataType__>::process_impl(gsl::index size) const
{
  for(size_t i = 0; i < inputFilters.size(); ++i)
  {
    inputFilters[i].set_pointer(converted_inputs[i], size);
  }
  for(size_t i = 0; i < outputFilters.size(); ++i)
  {
    outputFilters[i].set_pointer(outputs[i], size);
  }

  sink.process(size);
}

template class WrapFilter<int64_t>;
template class WrapFilter<float>;
template class WrapFilter<double>;
} // namespace ATK
