/*
* copyright (c) 2010 Sveriges Television AB <info@casparcg.com>
*
*  This file is part of CasparCG.
*
*    CasparCG is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    CasparCG is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with CasparCG.  If not, see <http://www.gnu.org/licenses/>.
*
*/
#pragma once

#include "fwd.h"

#include "pixel_format.h"
#include "write_frame.h"

#include "../format/video_format.h"

#include <common/utility/safe_ptr.h>

#include <tbb/concurrent_queue.h>

#include <boost/thread/future.hpp>

#include <memory>

namespace caspar { namespace core {

class frame_processor_device : boost::noncopyable
{
public:
	frame_processor_device(frame_processor_device&& other); // nothrow
	frame_processor_device(const video_format_desc& format_desc);
		
	safe_ptr<const read_frame> process(safe_ptr<draw_frame>&& frame); // nothrow
		
	safe_ptr<write_frame> create_frame(const pixel_format_desc& desc);		
	safe_ptr<write_frame> create_frame(size_t width, size_t height, pixel_format::type pix_fmt = pixel_format::bgra);			
	safe_ptr<write_frame> create_frame(pixel_format::type pix_fmt = pixel_format::bgra);
	
	const video_format_desc& get_video_format_desc() const; // nothrow
private:
	struct implementation;
	std::shared_ptr<implementation> impl_;
};

}}