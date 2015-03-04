//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 6:23:22 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __OBJECT_MODEL_H_95EC2F52_D13F_4621_82B0_1D426C0EC01C_
#define __OBJECT_MODEL_H_95EC2F52_D13F_4621_82B0_1D426C0EC01C_

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
	class object;

	/// underlying member type
	enum member_type
	{
		vt_invalid = 0,
		vt_float32,
		vt_float64,
		vt_int8,
		vt_uint8,
		vt_int16,
		vt_uint16,
		vt_int32,
		vt_uint32,
		vt_int64,
		vt_uint64,
		vt_string,
		vt_object,
		vt_bool
	};

	enum member_modifier
	{
		mt_array,
		mt_pointer
	};

	/// 
	struct member_value
	{
		union value_
		{
			core::float32	f32;
			core::float64	f64;
			core::int8		i8;
			core::uint8		ui8;
			core::int16		i16;
			core::uint16	ui16;
			core::int32		i32;
			core::uint32	ui32;
			core::int64		i64;
			core::uint64	ui64;
			const char*		str;
			object*			obj;
		} value;
		member_type type;
	};

	ENGINE_ABI int get_member_value_size(member_type t);
	ENGINE_ABI const char* to_string(member_type t);		
	ENGINE_ABI member_type from_string(const char*);
	
} // end namespace
} // end namespace

#endif // __OBJECT_MODEL_H_95EC2F52_D13F_4621_82B0_1D426C0EC01C_
