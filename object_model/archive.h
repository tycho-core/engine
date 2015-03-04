//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:27:40 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __ARCHIVE_H_53F3E779_E2E6_4EA8_AEC4_BE25AFFE6AEF_
#define __ARCHIVE_H_53F3E779_E2E6_4EA8_AEC4_BE25AFFE6AEF_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "core/types.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{

	/// archive base interface
    class ENGINE_ABI archive
    {
    public:
		virtual void begin_object(const char *type, const char *name, int version) = 0;
		virtual void end_object() = 0;
		virtual void begin_base_class(const char *type, int version) = 0;
		virtual void end_base_class() = 0;
		virtual void begin_array(const char *type, const char *name) = 0;
		virtual void end_array() = 0;
		virtual void write(const char *name, const char *type, const char*) = 0;
		virtual void write(const char *name, const char *type, char) = 0;
		virtual void write(const char *name, const char *type, int) = 0;
		virtual void write(const char *name, const char *type, core::int64) = 0;
		virtual void write(const char *name, const char *type, core::uint64) = 0;
		virtual void write(const char *name, const char *type, float) = 0;
		virtual void write(const char *name, const char *type, double) = 0;
		virtual void write(const char *name, const char *type, unsigned char) = 0;
		virtual void write(const char *name, const char *type, unsigned int) = 0;
	};

} // end namespace
} // end namespace

#endif // __ARCHIVE_H_53F3E779_E2E6_4EA8_AEC4_BE25AFFE6AEF_
