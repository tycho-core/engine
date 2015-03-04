//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:28:16 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __TEXT_OUTPUT_ARCHIVE_H_C8F874B9_17A9_4D50_8BB2_63DD70681DD7_
#define __TEXT_OUTPUT_ARCHIVE_H_C8F874B9_17A9_4D50_8BB2_63DD70681DD7_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "archive.h"
#include <ostream>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{

	/// implements a textual lined based format. A simple line based approach is used
	/// over XML for speed and ease of diffing.
    class ENGINE_ABI text_output_archive : public archive
    {
	public:
		text_output_archive(std::ostream &ostr);
		
		virtual void begin_object(const char *type, const char *name, int version);	
		virtual void end_object();
		virtual void begin_base_class(const char *type, int version);	
		virtual void end_base_class();
		virtual void begin_array(const char *type, const char *name);
		virtual void end_array();
		virtual void write(const char *name, const char *type, char c);
		virtual void write(const char *name, const char *type, int i);
		virtual void write(const char *name, const char *type, core::int64);
		virtual void write(const char *name, const char *type, core::uint64);			
		virtual void write(const char *name, const char *type, float f);			
		virtual void write(const char *name, const char *type, double d);
		virtual void write(const char *name, const char *type, unsigned char);
		virtual void write(const char *name, const char *type, unsigned int);
		virtual void write(const char *name, const char *type, const char *str);	
		
	private:
		void operator=(const text_output_archive&rhs);
		std::ostream &m_ostr;
    };

} // end namespace
} // end namespace

#endif // __TEXT_OUTPUT_ARCHIVE_H_C8F874B9_17A9_4D50_8BB2_63DD70681DD7_
