//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:20:46 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __OBJECT_H_E38D42B2_40D9_4D47_977F_62E64BB99273_
#define __OBJECT_H_E38D42B2_40D9_4D47_977F_62E64BB99273_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "object_model.h"
#include <string>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{

	class object_type_info;
	
	/// base of the object hierarchy
    class ENGINE_ABI object
    {
	public:	
		object(const char *name) :
			m_name(name)
			{ }

		virtual ~object() {}
			
		/// member access
		virtual const object_type_info* get_type_info() const { return ms_type_info; }
		
		const char* get_name() const { return m_name.c_str(); }
		virtual void* most_derived_ptr() { return this; }
		
		static void write_member(void *ptr, const char *name, const object_type_info *ti, member_value v);
		static member_value read_member(void *ptr, size_t i, const object_type_info *ti);
		
		/// type info
		static object_type_info* type_info();
			
	protected:	
		std::string m_name;       
		static object_type_info *ms_type_info;
    };

} // end namespace
} // end namespace

#endif // __OBJECT_H_E38D42B2_40D9_4D47_977F_62E64BB99273_
