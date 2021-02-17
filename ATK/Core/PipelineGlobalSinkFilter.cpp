/**
 * \file PipelineGlobalSinkFilter.cpp
 */

#include "PipelineGlobalSinkFilter.h"
#include <ATK/Core/Utilities.h>

#if ATK_USE_THREADPOOL == 1
#include <tbb/task_group.h>
#endif

#include <algorithm>

namespace ATK
{
  PipelineGlobalSinkFilter::PipelineGlobalSinkFilter()
  :Parent(0, 0)
  {
  }
  
  void PipelineGlobalSinkFilter::add_filter(gsl::not_null<BaseFilter*> filter)
  {
    if(std::find(filters.begin(), filters.end(), filter) == filters.end())
    {
      filters.push_back(filter);
    }
    else
    {
      throw RuntimeError("Try to ad a filter that was aleady added");
    }
  }

  void PipelineGlobalSinkFilter::remove_filter(gsl::not_null<const BaseFilter*> filter)
  {
    auto it = std::find(filters.begin(), filters.end(), filter);
    if(it != filters.end())
    {
      filters.erase(it);
    }
    else
    {
      throw RuntimeError("Try to remove a filter that was not added");
    }
  }

  int PipelineGlobalSinkFilter::get_type() const
  {
    return 0; // bogus
  }

  void PipelineGlobalSinkFilter::set_input_port(gsl::index input_port, gsl::not_null<BaseFilter*> filter, gsl::index output_port)
  {
    set_input_port(input_port, *filter, output_port);
  }

  void PipelineGlobalSinkFilter::set_input_port(gsl::index input_port, BaseFilter& filter, gsl::index output_port)
  {
    throw RuntimeError("This function must not be called on pipelines");
  }

  void PipelineGlobalSinkFilter::set_parallel(bool parallel)
  {
    activate_parallel = parallel;
  }

  void PipelineGlobalSinkFilter::prepare_process(gsl::index size)
  {
    // Nothing to do
  }

  void PipelineGlobalSinkFilter::prepare_outputs(gsl::index size )
  {
    // Nothing to do
  }

  void PipelineGlobalSinkFilter::dryrun(gsl::index size)
  {
    for(auto filter: filters)
    {
      filter->reset();
    }
    for(auto filter: filters)
    {
      filter->process_conditionnally<false>(uint64_t(size) * filter->get_output_sampling_rate() / input_sampling_rate);
    }
  }

  void PipelineGlobalSinkFilter::process_impl(gsl::index size ) const
  {
    for(auto filter: filters)
    {
      filter->reset();
    }
#if ATK_USE_THREADPOOL == 1
    if (activate_parallel)
    {
      tbb::task_group g;
      for(auto filter: filters)
      {
        g.run([=] {
          filter->process_conditionnally<true>(
              uint64_t(size) * (*it)->get_output_sampling_rate() / input_sampling_rate);
        });
      }
      g.wait();
      return;
    }
#endif
    for(auto filter: filters)
    {
      filter->process_conditionnally<true>(uint64_t(size) * filter->get_output_sampling_rate() / input_sampling_rate);
    }
  }

}
