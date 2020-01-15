/* -*- c++ -*- */

#define SCOPY_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "scopy_swig_doc.i"

%{
#include "scopy/analog_source.h"
%}


%include "scopy/analog_source.h"
GR_SWIG_BLOCK_MAGIC2(scopy, analog_source);
