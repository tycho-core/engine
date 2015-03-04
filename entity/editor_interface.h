//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Saturday, 5 April 2008 2:52:45 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __EDITOR_INTERFACE_H_05DE7628_4595_4903_8F43_163B6D5DC256_
#define __EDITOR_INTERFACE_H_05DE7628_4595_4903_8F43_163B6D5DC256_

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

	/// an entity exposes this interface if it wants allow editor interaction.
	/// this gives the editor a mechanism to query for editable parameters and
	/// sub objects and communicate their modification to the owning object.
    class ENGINE_ABI editor_interface
    {
    public:
    
    private:
    
    };

} // end namespace

} // end namespace

#endif // __EDITOR_INTERFACE_H_05DE7628_4595_4903_8F43_163B6D5DC256_
