//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:22:17 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __OBJECT_MANAGER_H_4AAA1714_052A_4694_8863_8219FA6A6E84_
#define __OBJECT_MANAGER_H_4AAA1714_052A_4694_8863_8219FA6A6E84_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include <map>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
	
	class object_type_info;

	/// factory for resolving names to types
    class ENGINE_ABI object_manager
    {
	public:
		static void register_type(object_type_info *type_info);
		
		/// allow unregistering so DLL's can contain new objects and be dynamically
		/// loaded and unloaded.
		static void unregister_type(object_type_info *type_info);
		
		/// lookup type info by name
		static object_type_info* lookup_type(const char *name);

		/// reset to default state
		static void clear();
		
	private:
		typedef std::map<std::string, object_type_info*> type_map;
		static type_map m_type_map;
	};

	#define REGISTER_OBJECT(name) \
		object_manager::register_type(new object_type_info<name>(#name))

} // end namespace
} // end namespace

#endif // __OBJECT_MANAGER_H_4AAA1714_052A_4694_8863_8219FA6A6E84_
