/* -*- c++ -*- */
/* 
 * Copyright 2019 Test.
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


#ifndef INCLUDED_SCOPY_TEST2_H
#define INCLUDED_SCOPY_TEST2_H

#include <scopy/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace scopy {

    /*!
     * \brief <+description of block+>
     * \ingroup scopy
     *
     */
    class SCOPY_API test2 : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<test2> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of scopy::test2.
       *
       * To avoid accidental use of raw pointers, scopy::test2's
       * constructor is in a private implementation
       * class. scopy::test2::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace scopy
} // namespace gr

#endif /* INCLUDED_SCOPY_TEST2_H */

