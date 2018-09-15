/**
 * \file Chebyshev1Filter.cpp
 */

#include <ATK/EQ/Chebyshev1Filter.hxx>

namespace ATK
{
  template class ATK_EQ_EXPORT Chebyshev1LowPassCoefficients<float>;
  template class ATK_EQ_EXPORT Chebyshev1LowPassCoefficients<double>;
  template class ATK_EQ_EXPORT Chebyshev1LowPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT Chebyshev1LowPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT Chebyshev1HighPassCoefficients<float>;
  template class ATK_EQ_EXPORT Chebyshev1HighPassCoefficients<double>;
  template class ATK_EQ_EXPORT Chebyshev1HighPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT Chebyshev1HighPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT Chebyshev1BandPassCoefficients<float>;
  template class ATK_EQ_EXPORT Chebyshev1BandPassCoefficients<double>;
  template class ATK_EQ_EXPORT Chebyshev1BandPassCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT Chebyshev1BandPassCoefficients<std::complex<double> >;
  template class ATK_EQ_EXPORT Chebyshev1BandStopCoefficients<float>;
  template class ATK_EQ_EXPORT Chebyshev1BandStopCoefficients<double>;
  template class ATK_EQ_EXPORT Chebyshev1BandStopCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT Chebyshev1BandStopCoefficients<std::complex<double> >;
}
