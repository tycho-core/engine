//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 25 March 2008 4:42:36 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine.h"
#include "entity/register_entites.h"
#include "slang/slang.h"
#include "object_model/object_manager.h"

namespace tycho
{
namespace engine
{

    /// initialise the tycho engine layer
    ENGINE_ABI void initialise()
    {
		static bool initialised = false;
		if(!initialised)
		{
			register_entities();			
			slang::initialise();
		}
    }

    /// shutdown the tycho engine layer
    ENGINE_ABI void shutdown()
    {
		slang::shutdown();
    }

} // end namespace
} // end namespace
