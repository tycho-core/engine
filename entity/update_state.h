//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Thursday, 10 April 2008 8:49:15 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __UPDATE_STATE_H_17BC5765_C3E2_412D_966B_EE6357BF5AE4_
#define __UPDATE_STATE_H_17BC5765_C3E2_412D_966B_EE6357BF5AE4_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
namespace entity
{
	class arena;
	
	/// per update information
	struct update_state 
	{
		entity::arena* arena; ///< arena this entity is in
		core::float64 secs;	 ///< number of seconds the simulation has been running
		core::float32 secs_elapsed; ///< number of seconds elapsed since the last update
		core::int64   tick;	 ///< number of ticks since the arena began
	};


} // end namespace
} // end namespace
} // end namespace

#endif // __UPDATE_STATE_H_17BC5765_C3E2_412D_966B_EE6357BF5AE4_
