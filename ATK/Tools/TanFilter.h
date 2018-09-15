/**
 * \file TanFilter.h
 */

#ifndef ATK_TOOLS_TANFILTER_H
#define ATK_TOOLS_TANFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Warps an analog frequency to a numeric one
  template<typename DataType_>
  class ATK_TOOLS_EXPORT TanFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    TanFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~TanFilter() override;

  protected:
    void process_impl(gsl::index size) const final;
    void setup() final;
  private:
    double coeff;
  };
}

#endif
