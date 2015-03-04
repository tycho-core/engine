//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:20:46 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "object.h"
#include "object_type_info.h"
#include "core/debug/assert.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace engine
{

	object_type_info* object::ms_type_info;
	
	member_value object::read_member(void *ptr, size_t i, const object_type_info *ti)
	{
		const object_member *om = ti->get_member(i);
		member_value value;
		value.type = om->m_type;
		int type_size = get_member_value_size(value.type);
		memcpy(&value.value, (char*)ptr + om->m_offset, type_size);			
		return value;
	}
	
	void object::write_member(void *ptr, const char *name, const object_type_info *ti, member_value v)
	{
		const object_member *om = ti->lookup_member(name);
		if(om)
		{
			TYCHO_ASSERT(v.type == om->m_type);
			int type_size = get_member_value_size(om->m_type);
			memcpy((char*)ptr + om->m_offset, &v.value, type_size);
		}
		else
		{
			/// \todo  error			
		}
	}		

} // end namespace
} // end namespace
