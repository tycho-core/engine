//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:28:27 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __TEXT_INPUT_ARCHIVE_H_A086B7D6_D6C0_4F4F_B212_D3337094FD56_
#define __TEXT_INPUT_ARCHIVE_H_A086B7D6_D6C0_4F4F_B212_D3337094FD56_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "object_model.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
	class archive;

	/// base input archive class. this presents an event based reader
	/// of input archives allowing reading without having the whole file 
	/// memory at once so is suitable for asynchronous reads. The buffer 
	/// is modified during processing to avoid copying data.
    class ENGINE_ABI text_input_archive
    {
    public:
		class reactor
		{
		public:
			virtual void parse_begin() = 0;
			virtual void parse_end() = 0;
			virtual void begin_object(const char *type, const char *name, int version) = 0;
			virtual void end_object() = 0;
			virtual void begin_base_class(const char *type, int version) = 0;
			virtual void end_base_class() = 0;
			virtual void begin_array(const char *type, const char *name) = 0;
			virtual void end_array() = 0;
			virtual void read_member(const char* name, member_value value) = 0;
		};
		
	public:
		text_input_archive(reactor *r);
		
		/// parse a buffer of text, this must be newline terminated
		void parse(char *ptr, int len);
		
	private:
		reactor*	m_reactor;	
    };

} // end namespace
} // end namespace

#endif // __TEXT_INPUT_ARCHIVE_H_A086B7D6_D6C0_4F4F_B212_D3337094FD56_
