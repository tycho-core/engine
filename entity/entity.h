//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Sunday, 23 March 2008 3:15:28 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __ENTITY_H_5CE9CE83_4A00_45CC_9776_2FB513AD621B_
#define __ENTITY_H_5CE9CE83_4A00_45CC_9776_2FB513AD621B_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "engine/entity/forward_decls.h"
#include "graphics/forward_decls.h"
#include "core/debug/assert.h"
#include <string>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
namespace entity
{

// 	interfaces
// 		i_animation
// 		i_rendering
// 		i_editor
// 		i_update
// 		i_serialize
// 		i_replicate
// 		i_ai
	
	
	/// an entity is an object that exists in the world, as such
	/// it can update and render etc.		
    class ENGINE_ABI entity_base
    {	
    public:		
		class render_interface;
		class animation_interface;
		class editor_interface;
		
    public:
		entity_base(const char *name) : m_ref_count(0), m_name(name)  { }
		virtual ~entity_base() { TYCHO_ASSERT(m_ref_count == 0); }
		void clone();
		
		/// get core interfaces
		virtual entity::render_interface*    get_render_interface() { return 0; }
		virtual entity::animation_interface* get_animation_interface() { return 0; }
		virtual entity::editor_interface*    get_editor_interface() { return 0; }

		/// entity interface
		virtual void update(update_state &) {}	
			
    private:
		TYCHO_INTRUSIVE_PTR_FRIEND_DECLS(ENGINE_ABI, entity_base)			
		int m_ref_count;		
		std::string m_name;
	
	protected:
		void add_ref() 
			{ ++m_ref_count; }
		void dec_ref() {  
			--m_ref_count;  
			if(m_ref_count == 0) 
				delete this;	
		}	
    };

	TYCHO_INTRUSIVE_PTR_FUNC_DECLS(ENGINE_ABI, entity_base)
	
} // end namespace

} // end namespace

} // end namespace

#endif // __ENTITY_H_5CE9CE83_4A00_45CC_9776_2FB513AD621B_
