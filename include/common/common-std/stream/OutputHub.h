/**
 * @file stream/OutputHub.h
 *
 * This file is part of EVEmu: EVE Online Server Emulator.<br>
 * Copyright (C) 2006-2011 The EVEmu Team<br>
 * For the latest information visit <i>http://evemu.org</i>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA, or go to
 * <i>http://www.gnu.org/copyleft/lesser.txt</i>.
 *
 * @author Bloody.Rabbit
 */

#ifndef __COMMON__STREAM__HUB_H__INCL__
#define __COMMON__STREAM__HUB_H__INCL__

#include "stream/Output.h"

namespace common
{
    namespace stream
    {
        /**
         * @brief A hub which duplicates output.
         *
         * @author Bloody.Rabbit
         */
        template< typename T >
        class OutputHub
        : public Output< T >
        {
            /// Our base for readability.
            typedef Output< T > Base;

        public:
            /// An element of the stream.
            typedef typename Base::Element Element;
            /// A type of the target stream.
            typedef Output< T > Target;

            /**
             * @brief A destructor, destroys the target streams.
             */
            ~OutputHub();

            /**
             * @brief Writes an element into all target streams.
             *
             * @param[in] e The element to be written.
             *
             * @return An error code.
             */
            Error Write( const Element& e );
            /**
             * @brief Writes elements into all target streams.
             *
             * @param[in]  ep           An array of elements to be written.
             * @param[in]  count        Length of the <var>ep</var> array.
             * @param[out] countWritten Where to store the number
             *                          of written elements.
             *
             * @return An error code.
             */
            Error Write( const Element* ep, size_t count, size_t* countWritten = NULL );

            /**
             * @brief Adds a target stream.
             *
             * The stream is destroyed in our destructor.
             *
             * @param[in] t The target stream.
             */
            void add( Target* t );
            /**
             * @brief Removes a target stream.
             *
             * The caller is responsible for destruction of
             * the stream.
             *
             * @param[in] t The target stream.
             */
            void remove( Target* t );

        protected:
            /// All target streams.
            std::set< Target* > mTargets;
        };

#       include "stream/OutputHub.inl"
    }
}

#endif /* !__COMMON__STREAM__HUB_H__INCL__ */