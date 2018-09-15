/**
 * \file ComplexConvertFilter.h
 */

#ifndef ATK_CORE_COMPLEXCONVERTFILTER_H
#define ATK_CORE_COMPLEXCONVERTFILTER_H

#include <complex>

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Core/config.h>

namespace ATK
{
  /// Converts two real channels into a complex one
  template<typename DataType_>
  class ATK_CORE_EXPORT RealToComplexFilter final : public TypedBaseFilter<DataType_, std::complex<DataType_>>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_, std::complex<DataType_>> Parent;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of channels, equal to the number of output channels, half the number of input ones
     */
    RealToComplexFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~RealToComplexFilter() override;
    
  protected:
    void process_impl(gsl::index size) const final;
  };

  /// Converts a complex channels into a two real one
  template<typename DataType_>
  class ATK_CORE_EXPORT ComplexToRealFilter final : public TypedBaseFilter<std::complex<DataType_>, DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<std::complex<DataType_>, DataType_> Parent;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of channels, equal to the number of input channels, half the number of output ones
    */
    ComplexToRealFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~ComplexToRealFilter() override;

  protected:
    void process_impl(gsl::index size) const final;
  };
}

#endif
