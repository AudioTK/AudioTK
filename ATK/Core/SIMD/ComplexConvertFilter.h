/**
 * \file ComplexConvertFilter.h
 */

#ifndef ATK_CORE_SIMD_COMPLEXCONVERTFILTER_H
#define ATK_CORE_SIMD_COMPLEXCONVERTFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Core/config.h>

namespace ATK
{
  /// Converts two real channels into a complex one
  template<typename DataType_, typename SIMDType>
  class ATK_CORE_EXPORT RealToComplexFilter final : public TypedBaseFilter<DataType_, SIMDType>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_, SIMDType> Parent;
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
  template<typename SIMDType, typename DataType__>
  class ATK_CORE_EXPORT ComplexToRealFilter final : public TypedBaseFilter<SIMDType, DataType__>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<SIMDType, DataType__> Parent;
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

  /// Create a filter to convert real streams to SIMD ones
  template<typename DataType_>
  ATK_CORE_EXPORT std::unique_ptr<BaseFilter> createRealToComplexFilter(gsl::index nb_channels = 1);
  /// Create a filter to convert SIMD streams to real ones
  template<typename DataType_>
  ATK_CORE_EXPORT std::unique_ptr<BaseFilter> createComplexToRealFilter(gsl::index nb_channels = 1);
}

#endif
