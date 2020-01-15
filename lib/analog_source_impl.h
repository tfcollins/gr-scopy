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

#ifndef INCLUDED_SCOPY_ANALOG_SOURCE_IMPL_H
#define INCLUDED_SCOPY_ANALOG_SOURCE_IMPL_H

#include <scopy/analog_source.h>

#include <libm2k/m2k.hpp>
#include <libm2k/contextbuilder.hpp>
#include <libm2k/analog/m2kpowersupply.hpp>
#include <libm2k/analog/m2kanalogin.hpp>
#include <libm2k/analog/m2kanalogout.hpp>

using namespace libm2k;
using namespace libm2k::analog;
using namespace libm2k::devices;

namespace gr {
  namespace scopy {

    class analog_source_impl : public analog_source
    {
     private:
       M2k *m_ctx;
       M2kAnalogIn *m_ain;
       unsigned int m_buffer_size;
       unsigned int m_num_channels;
       const std::string m_uri;


     public:
      analog_source_impl(const std::string &uri, const std::vector<std::string> &channels, unsigned int buffer_size);
      ~analog_source_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace scopy
} // namespace gr

#endif /* INCLUDED_SCOPY_ANALOG_SOURCE_IMPL_H */
