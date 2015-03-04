//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 6:23:22 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "object_model.h"
#include "core/string.h"
#include "core/debug/assert.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace engine
{

	const char* message_type_strings[] = {
		"invalid",
		"f32",
		"f64",
		"i8",
		"ui8",
		"i16",
		"ui16",
		"i32",
		"ui32",
		"i64",
		"ui64",			
		"str",
		"obj",
		"bool",
		0
	};

	ENGINE_ABI const char* to_string(member_type t)
	{
		return message_type_strings[t];
	}

	ENGINE_ABI member_type from_string(const char *str)
	{
		const char **s = message_type_strings;
		
		for(int i = 0; *s; ++s, ++i)
		{
			if(core::strcmp(*s, str) == 0)
				return (member_type)i;
		}
		return vt_invalid;
	}

    ENGINE_ABI int get_member_value_size(member_type t)
	{
		switch(t)
		{
			case vt_int8	:
			case vt_uint8	: return 1;
                
			case vt_int16	:
			case vt_uint16	: return 2;
                
                //COMPAT : object is a ptr but using 32bits, problem on 64bit.
			case vt_object  :
			case vt_float32	:
			case vt_string	:
			case vt_int32	:
			case vt_uint32	:
			case vt_bool	: return 4;
                
			case vt_float64	:
			case vt_int64	:
			case vt_uint64	: return 8;
                
            default: TYCHO_NOT_IMPLEMENTED; break;
                
		}
		return 0;
	}

} // end namespace
} // end namespace
