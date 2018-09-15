/**
 * \file MaxFilter.h
 */

#ifndef ATK_TOOLS_MAXFILTER_H
#define ATK_TOOLS_MAXFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Returns the maximum of two signals in one
  template<typename DataType_>
  class ATK_TOOLS_EXPORT MaxFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_output_ports;
    using Parent::nb_input_ports;

  public:
    /*!
    * @brief Constructor
    */
    MaxFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~MaxFilter() override;
    
  protected:
    void process_impl(gsl::index size) const final;
  };
}

#endif
