/**
 * \file WrapFilter.h
 */

#ifndef ATK_CORE_WRAPFILTER_H
#define ATK_CORE_WRAPFILTER_H

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/PipelineGlobalSinkFilter.h>
#include <ATK/Core/TypedBaseFilter.h>

#include <vector>

namespace ATK
{
/// Class that can be used to wrap a set of filters.
template <typename DataType_, typename DataType__ = DataType_>
class ATK_CORE_EXPORT WrapFilter final: public TypedBaseFilter<DataType_, DataType__>
{
protected:
  /// Simplify parent calls
  using Parent = TypedBaseFilter<DataType_, DataType__>;
  using Parent::converted_inputs;
  using Parent::get_input_sampling_rate;
  using Parent::get_output_sampling_rate;
  using Parent::outputs;
  using Parent::process_conditionnally;
  using Parent::reset;

public:
  /// Constructor of the wrapper
  WrapFilter(gsl::index nb_input_ports,
      gsl::index nb_output_ports,
      const std::function<void(std::vector<InPointerFilter<DataType_>>& inputFilters,
          std::vector<OutPointerFilter<DataType__>>& outputFilters,
          std::vector<gsl::unique_ptr<BaseFilter>>& filters)>& fun);
  /// destructor
  ~WrapFilter() override = default;

  void full_setup() override;

  /// Dry run the internal filters
  void dry_run(gsl::index size);

protected:
  void process_impl(gsl::index size) const final;

  mutable std::vector<InPointerFilter<DataType_>> inputFilters;
  mutable std::vector<OutPointerFilter<DataType__>> outputFilters;
  /// List of filters in this wrapped filters
  std::vector<gsl::unique_ptr<BaseFilter>> filters;
  mutable PipelineGlobalSinkFilter sink;
};
} // namespace ATK

#endif
