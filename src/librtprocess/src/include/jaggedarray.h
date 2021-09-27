/*
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2016 Ingo Weyrich <heckflosse67@gmx.de>
 *  Copyright (c) 2016 Adam Reichold <adam.reichold@t-online.de>
 *
 *  RawTherapee is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  RawTherapee is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RawTherapee.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <cstring>

namespace librtprocess
{

// These emulate a jagged array, but use only 2 allocations instead of 1 + H.

template<typename T>
class JaggedArray
{
public:
    explicit JaggedArray(const JaggedArray&) = delete;
    JaggedArray& operator =(const JaggedArray&) = delete;

    JaggedArray(std::size_t width, std::size_t height, bool init_zero = false) :
        array(
            [width, height, init_zero]() -> T**
            {
                T** const res = new (std::nothrow) T*[height];
                if (res) {
                    res[0] = new (std::nothrow)T[height * width];

                    for (std::size_t i = 1; i < height; ++i) {
                        res[i] = res[i - 1] + width;
                    }

                    if (res[0] && init_zero) {
                        std::memset(res[0], 0, sizeof(T) * width * height);
                    }
                } else {
                    res[0] = nullptr;
                }
                return res;
            }()
        )
    {
    }

    ~JaggedArray ()
    {
        delete[] array[0];
        delete[] array;
    }

    operator T** ()
    {
        return array;
    }

    operator bool()
    {
        return array && array[0];
    }

private:
    T** const array;

};

} // rtengine
