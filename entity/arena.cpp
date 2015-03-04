//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 31 March 2008 10:01:53 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "arena.h"
#include "engine/entity/entity.h"
#include "engine/entity/update_state.h"
#include "engine/entity/render_interface.h"
#include "core/debug/assert.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace engine
{
namespace entity
{
	/// default constructor
	arena::arena(graphics::renderer_ptr r) :
		m_renderer(r),
		m_updating(false)
	{
	
	}
	
	/// destructor
	arena::~arena()
	{
	}
	
	/// update the arena
	void arena::update(update_state &state)
	{
		m_updating = true;
		
		// update all entities 
		{
			entity_set::iterator it = m_entities.begin();
			entity_set::iterator end = m_entities.end();
			for(; it != end; ++it)
			{
				(*it)->update(state);
			}		
		}
		
		// Update any that were created in the initial update loop, new objects are pushed on the 
		// back as we go and this does not invalidate iterators so we can just keep going until we 
		// hit the end of the list . We want to make sure that any entities get an update the tick they are created 
		// this is to remove the one tick delay that would occur otherwise. Another benefit of this is 
		// that when we put in the cleanup sweep of unused entities at the end of the update it gives
		// new entities a chance to form ties to other entities that would be deleted this update and
		// so would be deleted then just recreated the next update, dunno if this happens in practice
		// but would be interesting to test for later when its under a realistic load.
		{
			entity_list::iterator it = m_objects_create_this_update.begin();
			entity_list::iterator end = m_objects_create_this_update.end();
			while(it != end)
			{
				(*it)->update(state);
			}
		}
		
		/// \todo  clean up anything that has reached a ref count of one (which is our reference)
		m_updating = false;		
	}
	
	/// render the arena
	void arena::render(graphics::renderer_ptr r, graphics::camera_ptr c)
	{
		entity_set::iterator it = m_entities.begin();
		entity_set::iterator end = m_entities.end();
		for(; it != end; ++it)
		{
			entity::render_interface *ri = (*it)->get_render_interface();
			if(ri)
				ri->render(r, c);
		}			
	}	
	
	/// add an entity to the world
	void arena::add_entity(entity_base_ptr e)
	{
		if(m_updating)
			m_objects_create_this_update.push_back(e);					
		m_entities.insert(e);
	}
	
	/// remove an entity from the world
	void arena::remove_entity(entity_base_ptr e)
	{
		entity_set::iterator it = m_entities.find(e);
		TYCHO_ASSERT(it != m_entities.end());
		m_entities.erase(it);
	}

	/// create a new entity by name
	entity_base_ptr arena::create_entity(const char *type_name, const char *name)
	{
/*		object_type_info *type = object_manager::lookup_type(type_name);
		TYCHO_ASSERT(type);
		if(!type)
			return entity_base_ptr();
		entity_base_ptr ptr((entity_base*)type->create_object(name));		
		add_entity(ptr);
		return ptr;
*/
		return entity_base_ptr();
	}

} // end namespace
} // end namespace
} // end namespace
