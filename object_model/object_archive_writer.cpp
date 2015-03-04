//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 8:10:17 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "object_archive_writer.h"
#include "archive.h"
#include "object.h"
#include "object_type_info.h"
#include "core/debug/assert.h"
#include <set>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace engine
{

	typedef std::set<object*> object_set;
	
	/// constructor
	object_archive_writer::object_archive_writer(archive *output_archive) :
		m_output_archive(output_archive)
	{		
	}
	
	void gather_objects(object_set &objects, object *obj)
	{
		if(!obj)
			return;
			
		if(objects.find(obj) != objects.end())
			return;
		
		objects.insert(obj);			
		
		const object_type_info* ti = obj->get_type_info();
		for(size_t i = 0; i < ti->num_members(); ++i)
		{
			TYCHO_ASSERT(ti->get_member(i));
			member_value v = object::read_member(obj->most_derived_ptr(), i, ti);
			if(v.type == vt_object)
			{
				gather_objects(objects, v.value.obj);
			}			
		}
	}
	
	/// write entire object tree to the archive
	void object_archive_writer::write(object *root)
	{
		// gather all unique objects in the tree
		object_set objects;
		gather_objects(objects, root);
		
		// write out all objects
		object_set::iterator it = objects.begin();
		object_set::iterator end = objects.end();
		while(it != end)
		{
			write_object(*it, (*it)->get_type_info(), false);
			++it;
		}			
	}
	
	void object_archive_writer::write_object(void *obj_ptr, const object_type_info *ti, bool is_base)
	{
		if(is_base)
			m_output_archive->begin_base_class(ti->get_name(), ti->get_version());
		else
		{
			object *obj = (object*)obj_ptr;
			m_output_archive->begin_object(ti->get_name(), obj->get_name(), ti->get_version());
		}
				
		// write base classes
		for(size_t i = 0; i < ti->num_base_classes(); ++i)
		{
			const object_type_info *base_type = ti->get_base_class(i);
			write_object(ti->cast(obj_ptr, base_type), base_type, true);
		}
					
		// write this objects members out
		TYCHO_ASSERT(ti);
		for(size_t i = 0; i < ti->num_members(); ++i)
		{
			const object_member *om = ti->get_member(i);
			TYCHO_ASSERT(om);
			member_value v = object::read_member(obj_ptr, i, ti);
			switch(v.type)
			{
				case vt_int8	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.i8); break;
				case vt_uint8	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.ui8); break;				
				case vt_int16	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.i16); break;
				case vt_uint16	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.i16); break;					
				case vt_float32	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.f32); break;
				case vt_string	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.str); break;
				case vt_int32	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.i32); break;
				case vt_uint32	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.ui32); break;									
				case vt_bool	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.i32); break;					
				case vt_float64	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.f64); break;
				case vt_int64	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.i64); break;
				case vt_uint64	: m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.ui64); break;

				case vt_object	: {
					// check to see if we have written this object before
					m_output_archive->write(om->m_name.c_str(), to_string(om->m_type), v.value.obj->get_name()); 
				} break;
                    
                default: TYCHO_NOT_IMPLEMENTED; break;
			}
		}						
		if(is_base)
			m_output_archive->end_base_class();
		else
			m_output_archive->end_object();
	}


} // end namespace
} // end namespace
