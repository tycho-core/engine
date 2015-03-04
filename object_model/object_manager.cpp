//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:22:17 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "object_manager.h"
#include "object_type_info.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace engine
{

	object_manager::type_map object_manager::m_type_map;

	void object_manager::register_type(object_type_info *type_info)
	{
		m_type_map.insert(std::make_pair(type_info->get_name(), type_info));
	}
	
	/// allow unregistering so DLL's can contain new objects and be dynamically
	/// loaded and unloaded.
	void object_manager::unregister_type(object_type_info *)
	{
	
	}
	
	object_type_info* object_manager::lookup_type(const char *name)
	{
		type_map::iterator it = m_type_map.find(name);
		if(it == m_type_map.end())
			return 0;
		return it->second;
	}

	/// reset to default state
	void object_manager::clear()
	{
		type_map::const_iterator it = m_type_map.begin();
		type_map::const_iterator end = m_type_map.end();
		
		for(; it != end; ++it)
		{
			delete it->second;
		}
		m_type_map.clear();
	}


} // end namespace
} // end namespace
