/*****************************************************************************
 *   Copyright (C) 2004-2009 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *   http://apps.sourceforge.net/mediawiki/pagmo                             *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Developers  *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Credits     *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#ifndef PAGMO_SERIALIZATION_H
#define PAGMO_SERIALIZATION_H

// Headers needed for serialization purposes.
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/graph/adj_list_serialize.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

// Serialization of circular buffer.
#include <boost/circular_buffer.hpp>

namespace boost { namespace serialization {

template <class Archive, class T>
void save(Archive &ar, const boost::circular_buffer<T> &cb, unsigned int)
{
	// Let's first save capacity and size.
	typedef typename boost::circular_buffer<T>::capacity_type capacity_type;
	typedef typename boost::circular_buffer<T>::size_type size_type;
	capacity_type capacity = cb.capacity();
	ar << capacity;
	size_type size = cb.size();
	ar << size;
	// Save the content.
	for (size_type i = 0; i < size; ++i) {
		ar << cb[i];
	}
}

template <class Archive, class T>
void load(Archive &ar, boost::circular_buffer<T> &cb, unsigned int)
{
	typedef typename boost::circular_buffer<T>::capacity_type capacity_type;
	typedef typename boost::circular_buffer<T>::size_type size_type;
	// Restore capacity.
	capacity_type capacity;
	ar >> capacity;
	cb.set_capacity(capacity);
	// Restore size.
	size_type size;
	ar >> size;
	cb.resize(size);
	// Restore elements.
	for (size_type i = 0; i < size; ++i) {
		ar >> cb[i];
	}
}

template <class Archive, class T>
void serialize(Archive &ar, boost::circular_buffer<T> &cb, const unsigned int file_version)
{
	split_free(ar, cb, file_version);
}

}}

#endif
