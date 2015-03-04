//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Saturday, 5 April 2008 2:51:26 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __RENDER_INTERFACE_H_8C2525B0_4A8B_44D6_9B49_8A9E23D870A1_
#define __RENDER_INTERFACE_H_8C2525B0_4A8B_44D6_9B49_8A9E23D870A1_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "graphics/forward_decls.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
namespace entity
{

	/// abstract interface for entity rendering. we use this style so
	/// the entity has great freedom when it comes to render time and
	/// also as we need to present a more complex interface due to
	/// the multithreaded renderer (when its here...)
    class ENGINE_ABI render_interface
    {
    public:
		virtual void render(graphics::renderer_ptr, graphics::camera_ptr) = 0;    
    };

} // end namespace
} // end namespace
} // end namespace

#endif // __RENDER_INTERFACE_H_8C2525B0_4A8B_44D6_9B49_8A9E23D870A1_
