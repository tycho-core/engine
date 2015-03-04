//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 6:25:37 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __OBJECT_MODULE_H_A1B7FA7F_2BB5_41EE_AC8D_A151DFD9D7B9_
#define __OBJECT_MODULE_H_A1B7FA7F_2BB5_41EE_AC8D_A151DFD9D7B9_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "object.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{

	/// module symbol table
	class ENGINE_ABI symbol_table
	{

	};

	/// a module is a collection of objects used for arbitrary grouping for convenience
	/// and efficiency.
	/// \todo  can we delay load objects until they are first referenced?
    class ENGINE_ABI object_module : public object
    {
    public:
		object_module(const char* name) : object(name) {}
		/// load the module
		bool load(const char *);
		
	private:
		symbol_table* m_imports; ///< objects this module imports from other modules
		symbol_table* m_exports; ///< objects this module exports to other modules
		object*		  m_root;	 ///< root of all objects in this module
	};

} // end namespace
} // end namespace

#endif // __OBJECT_MODULE_H_A1B7FA7F_2BB5_41EE_AC8D_A151DFD9D7B9_
