/* Authors: Lutong Wang and Bangqi Xu */
/*
 * Copyright (c) 2019, The Regents of the University of California
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <algorithm>

#include "frBaseTypes.h"

namespace drt {
class frEndStyle
{
 public:
  // constructor
  frEndStyle() = default;
  frEndStyle(const frEndStyle& styleIn) = default;
  frEndStyle(frEndStyleEnum styleIn) : style_(styleIn) {}
  // setters
  void set(frEndStyleEnum styleIn) { style_ = styleIn; }
  void set(const frEndStyle& styleIn) { style_ = styleIn.style_; }
  // getters
  operator frEndStyleEnum() const { return style_; }

 private:
  frEndStyleEnum style_{frcExtendEndStyle};

  template <class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    (ar) & style_;
  }

  friend class boost::serialization::access;
};

class frSegStyle
{
 public:
  // constructor
  frSegStyle() = default;
  frSegStyle(const frSegStyle& in) = default;
  // setters
  void setWidth(frUInt4 widthIn) { width_ = widthIn; }
  void setBeginStyle(const frEndStyle& style, frUInt4 ext = 0)
  {
    beginStyle_.set(style);
    beginExt_ = ext;
  }
  void setEndStyle(const frEndStyle& style, frUInt4 ext = 0)
  {
    endStyle_.set(style);
    endExt_ = ext;
  }
  void setBeginExt(const frUInt4& in) { beginExt_ = in; }
  void setEndExt(const frUInt4& in) { endExt_ = in; }
  // getters
  frUInt4 getWidth() const { return width_; }
  frUInt4 getBeginExt() const { return beginExt_; }
  frEndStyle getBeginStyle() const { return beginStyle_; }
  frUInt4 getEndExt() const { return endExt_; }
  frEndStyle getEndStyle() const { return endStyle_; }

  void swap()
  {
    std::swap(beginExt_, endExt_);
    std::swap(beginStyle_, endStyle_);
  }

 private:
  frUInt4 beginExt_{0};
  frUInt4 endExt_{0};
  frUInt4 width_{0};
  frEndStyle beginStyle_;
  frEndStyle endStyle_;

  template <class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    (ar) & beginExt_;
    (ar) & endExt_;
    (ar) & width_;
    (ar) & beginStyle_;
    (ar) & endStyle_;
  }

  friend class boost::serialization::access;
};

}  // namespace drt
