/*
 ==============================================================================
 
 This file is part of the ATK library.
 Copyright (c) 2017 - Matthieu Brucher
 
 ATK is an open source library subject to the BSD licnse.
 
 ==============================================================================
 */

/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               atk_special
  vendor:           Matthieu Brucher
  version:          3.3.0
  name:             ATK Special
  description:      Special classes for ATK
  website:          http://www.audio-tk.com/
  license:          BSD

  dependencies:     atk_core
  OSXFrameworks:
  iOSFrameworks:

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#ifndef ATK_SPECIAL
#define ATK_SPECIAL

#if (ATK_USE_FFTW == 1) or (ATK_USE_IPP == 1)
# include <ATK/Special/ConvolutionFilter.h>
#endif

#endif
