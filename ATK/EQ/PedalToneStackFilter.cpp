/**
 * \file PedalToneStackFilter.cpp
 */

#include <ATK/EQ/PedalToneStackFilter.hxx>
#include <ATK/EQ/IIRFilter.h>

namespace ATK
{
  template class ATK_EQ_EXPORT SD1ToneCoefficients<float>;
  template class ATK_EQ_EXPORT SD1ToneCoefficients<double>;
  template class ATK_EQ_EXPORT SD1ToneCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT SD1ToneCoefficients<std::complex<double> >;
  
  template class ATK_EQ_EXPORT TS9ToneCoefficients<float>;
  template class ATK_EQ_EXPORT TS9ToneCoefficients<double>;
  template class ATK_EQ_EXPORT TS9ToneCoefficients<std::complex<float> >;
  template class ATK_EQ_EXPORT TS9ToneCoefficients<std::complex<double> >;
}
