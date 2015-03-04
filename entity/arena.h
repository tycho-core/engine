//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 31 March 2008 10:01:53 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __ENTITY_ARENA_H_F047F071_53FE_47DB_BA66_81200C66D3EF_
#define __ENTITY_ARENA_H_F047F071_53FE_47DB_BA66_81200C66D3EF_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "engine/entity/forward_decls.h"
#include "graphics/forward_decls.h"
#include <list>
#include <set>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
namespace entity
{

	/// an entity_arena a collection of entities and is isolated from all other arena's. 
	/// This allows multiples 'worlds' to exist independently from each other, for instance 
	/// play in a in editor mode or as streaming areas or as a game level.
    class ENGINE_ABI arena
    {
    public:
		/// default constructor
		/// \param renderer Renderer to use when drawing this arena
		arena(graphics::renderer_ptr renderer);
		
		/// destructor
		~arena();
		
		/// update the arena
		void update(update_state &state);
		
		/// render the arena
		void render(graphics::renderer_ptr, graphics::camera_ptr );
		
		/// add an entity to the world
		void add_entity(entity_base_ptr);
		
		/// remove an entity from the world
		void remove_entity(entity_base_ptr);

		/// create a new entity by name
		entity_base_ptr create_entity(const char *type, const char *name);
		
		/// lookup an entity by path name, returns 0 if it does not exist.
		/// path is the form name.name from the root of the arena.
		entity_base_ptr lookup_entity_by_path(const char *path);
		
		/// \returns the renderer this arena uses
		graphics::renderer_ptr get_renderer() { return m_renderer; }
		        
    private:
		typedef std::set<entity_base_ptr>	entity_set;
		typedef std::list<entity_base_ptr>	entity_list;
		entity_set		m_entities;
		entity_list		m_objects_create_this_update;
		graphics::renderer_ptr m_renderer;
		bool			m_updating;
    };

} // end namespace

} // end namespace

} // end namespace

#endif // __ENTITY_ARENA_H_F047F071_53FE_47DB_BA66_81200C66D3EF_
