//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 2 April 2008 12:42:37 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __FORWARD_DECLS_H_44767BA7_564A_4419_8486_ED34D41398EA_
#define __FORWARD_DECLS_H_44767BA7_564A_4419_8486_ED34D41398EA_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "core/intrusive_ptr.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
namespace entity
{
	// management
	class ENGINE_ABI arena;

	// interfaces
	class ENGINE_ABI render_interface;
	class ENGINE_ABI editor_interface;
	class ENGINE_ABI animation_interface;

	// entities
	TYCHO_DECLARE_INTRUSIVE_PTR(ENGINE_ABI, entity_base)
	TYCHO_DECLARE_INTRUSIVE_PTR(ENGINE_ABI, mesh)
	TYCHO_DECLARE_INTRUSIVE_PTR(ENGINE_ABI, camera)
	
	// other
	struct update_state;
	
} // end namespace
	
} // end namespace

} // end namespace

#endif // __FORWARD_DECLS_H_44767BA7_564A_4419_8486_ED34D41398EA_
