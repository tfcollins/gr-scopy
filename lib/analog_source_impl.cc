/* -*- c++ -*- */
/*
 * Copyright 2019 Travis F. Collins <travis.collins@analog.com>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "analog_source_impl.h"
#include <boost/lexical_cast.hpp>

using namespace libm2k;
using namespace libm2k::analog;
using namespace libm2k::devices;

namespace gr {
  namespace scopy {

    analog_source::sptr
    analog_source::make(const std::string &uri, const std::vector<std::string> &channels, unsigned int buffer_size)
    {
      return gnuradio::get_initial_sptr
        (new analog_source_impl(uri, channels, buffer_size));
    }

    /*
     * The private constructor
     */
    analog_source_impl::analog_source_impl(const std::string &uri, const std::vector<std::string> &channels, unsigned int buffer_size)
      : gr::sync_block("analog_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, channels.size(), sizeof(float) ) ),
        m_buffer_size(buffer_size),
        m_uri(uri)
    {

      std::cout<<"Channels "<<channels.size()<<"\n";
      if (uri.length()==0)
      {
        m_ctx = libm2k::devices::m2kOpen();
      }
      else
        m_ctx = libm2k::devices::m2kOpen(uri.c_str());

      // Calibrate
      m_ctx->calibrateADC();
    	m_ctx->calibrateDAC();

      // Get analog
      m_ain = m_ctx->getAnalogIn();

      m_num_channels = channels.size();
      int k;
      for (k=0;k<m_num_channels;k++)
        m_ain->enableChannel(k, true);

      m_ain->setSampleRate(100000);
      m_ain->setRange((ANALOG_IN_CHANNEL)0,-10.0,10.0); // nu are idxchannel
      // m_ain->setRange((ANALOG_IN_CHANNEL)1,PLUS_MINUS_25V);

      set_output_multiple(buffer_size);
    }

    /*
     * Our virtual destructor.
     */
    analog_source_impl::~analog_source_impl()
    {
    }

    int
    analog_source_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      int k,c, process;
      float *out;// = (double *) output_items[0];

      auto data = m_ain->getSamples(m_buffer_size);

      if (noutput_items>m_buffer_size)
        noutput_items = m_buffer_size;

      for(c=0; c<output_items.size(); c++)
      {
        out = (float*) output_items[c];
        for(k=0; k<noutput_items; k++)
        {
          out[k] =  boost::lexical_cast<float>(data[c][k]);
        }
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace scopy */
} /* namespace gr */
