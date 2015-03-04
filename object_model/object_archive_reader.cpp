//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:48:49 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "object_archive_reader.h"
#include "object_type_info.h"
#include "object_manager.h"
#include "object.h"
#include "core/debug/assert.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace engine
{

	object_archive_reader::object_archive_reader() :
		m_cur_obj(0),
		m_root(0),
		m_cur_base(0),
		m_cur_base_type(0)
	{
	
	}

	void object_archive_reader::parse_begin()
	{
	
	}
	
	void object_archive_reader::parse_end()
	{
		// patch up all object references that couldn't be resolved during the parsing
		object_link_map::iterator it  = m_object_links.begin();
		object_link_map::iterator end = m_object_links.end();
		while(it != end)
		{
			object_link &link = it->second;
			if(!link.obj)
			{
				std::cout << "Unresolved reference to " << link.name << "\n";
			}
			else
			{
				for(size_t i = 0; i < link.links.size(); ++i)
				{
					object_link::link &l = link.links[i];
					member_value value;
					value.type = vt_object;
					value.value.obj = link.obj;
					object::write_member(l.o, l.om->m_name.c_str(), l.o->get_type_info(), value);
				}
			}
			++it;
		}
	}

	void object_archive_reader::begin_object(const char *type, const char *name, int /*version*/)
	{
		// see if we have encountered this object before
		object_link_map::iterator it = m_object_links.find(name);
		if(it == m_object_links.end())
		{
			it = m_object_links.insert(m_object_links.begin(), std::make_pair(name, object_link()));				
			it->second.name = name;
		}
		object_link &link = it->second;						
		if(link.obj == 0)
		{
			// lookup type in the type factory
			object_type_info* type_info = object_manager::lookup_type(type);
			TYCHO_ASSERT(type_info);
			object *new_obj = type_info->create_object(name);
			TYCHO_ASSERT(new_obj);		
			m_cur_obj = new_obj;		
			link.obj = new_obj;		
		}
		else
		{
			std::cout << "duplicate object definition for " << name << "\n";
		}
		
		// root is the first object in the file
		if(!m_root)
			m_root = m_cur_obj;						
	}
	
	void object_archive_reader::begin_base_class(const char *type, int /*version*/)
	{
		const object_type_info *base_type = object_manager::lookup_type(type);
		// need offset to base class object
		m_cur_base = m_cur_obj->get_type_info()->cast(m_cur_obj, base_type);
		m_cur_base_type = base_type;
	}
	
	void object_archive_reader::end_base_class()
	{
		m_cur_base_type = 0;
		m_cur_base = 0;
	}
	
	void object_archive_reader::end_object()
	{
		m_cur_obj = 0;
	}
	
	void object_archive_reader::begin_array(const char * /*type*/, const char * /*name*/)
	{
	
	}
	
	void object_archive_reader::end_array()
	{
	
	}
	
	void object_archive_reader::read_member(const char* name, member_value value)
	{
		// handle object linking, we need to remember all objects and arrays we have created and 
		// post load go back and patch them up to there actual locations. This way we avoid all
		// dependencies in the file content and allow for circular references.
		if(value.type == vt_object)
		{				
			// at this point the value refers to a strings representing the real object
			// so add this object to the list of those to remember for patching up later
			
			// see if we have encountered this object before
			object_link_map::iterator it = m_object_links.find(value.value.str);
			
			// if not add a link to it 
			if(it == m_object_links.end())
			{
				it = m_object_links.insert(m_object_links.begin(), std::make_pair(value.value.str, object_link()));
				it->second.name = value.value.str;
			}	
			object_link &link = it->second;
			
			// if we have then set this member immediately
			if(link.obj)
			{
				value.value.obj = link.obj;
				m_cur_obj->write_member(m_cur_obj->most_derived_ptr(), name, m_cur_obj->get_type_info(), value);					
			}
			else
			{
				// add this member to the object link for patching up later
				const object_type_info *ti = m_cur_obj->get_type_info();
				const object_member *om = ti->lookup_member(name);
				object_link::link new_link;
				new_link.o = m_cur_obj;	
				new_link.om = om;
				link.links.push_back(new_link);			
			}					
		}
			
		if(m_cur_base)			
			m_cur_obj->write_member(m_cur_base, name, m_cur_base_type, value);
		else
			m_cur_obj->write_member(m_cur_obj->most_derived_ptr(), name, m_cur_obj->get_type_info(), value);
	}
	
	

	
} // end namespace
} // end namespace
