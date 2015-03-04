//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:23:41 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "object_type_info.h"
#include "object.h"
#include "core/debug/assert.h"
#include "core/string.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace engine
{

	/// constructor
	object_type_info::object_type_info(const char *name, int version, object_create_func create_func) :
        m_create_func(create_func),
        m_legacy_loader_func(0),
		m_name(name),
		m_version(version)
	{
	}
	
	/// destructor
	object_type_info::~object_type_info()
	{
		for(size_t i = 0; i < m_members.size(); ++i)
			delete m_members[i];
		m_members.clear();
	}	

	/// set legacy version loader
	void object_type_info::set_legacy_loader_func(legacy_loader_func f)
	{
		m_legacy_loader_func = f;
	}
	
	/// call the function to handle legacy versions of this type
	void object_type_info::call_legacy_loader_func(object_archive_reader *reader, int version)
	{
		if(m_legacy_loader_func)
			(*m_legacy_loader_func)(reader, version);
	}

	/// create a new instance of this object        
	object* object_type_info::create_object(const char *name) const
	{
		return (*m_create_func)(name);
	}

	/// lookup a member index by name
	const object_member* object_type_info::lookup_member(const char *name) const
	{
		TYCHO_ASSERT(name);
		
		for(size_t i = 0; i < num_members(); ++i)
		{
			const object_member *om = get_member(i);
			TYCHO_ASSERT(om);
			int res = om->m_name.compare(name);
			if(res == 0)
			{
				return om;
			}
		}
		return 0;
	}

	/// lookup a base class by name
	const object_type_info::base_class* object_type_info::lookup_base_class(const char *name) const
	{
		TYCHO_ASSERT(name);
		
		for(size_t i = 0; i < m_base_classes.size(); ++i)
		{
			const base_class *bc = &m_base_classes[i];
			TYCHO_ASSERT(bc);
			int res = core::strcmp(bc->ti->get_name(), name);
			if(res == 0)
			{
				return bc;
			}
		}
		return 0;
	}

	void object_type_info::add_base_class(const object_type_info *base, int fixup)
	{
		base_class b;
		b.ti = base;
		b.ptr_fixup = fixup;
		m_base_classes.push_back(b);
	}
	
	/// cast the pointer of this type to that of a base class type
	void* object_type_info::cast(void *ptr, const object_type_info *ti) const
	{
		const base_class *base = lookup_base_class(ti->get_name());
		if(base)
		{
			return (char*)ptr + base->ptr_fixup;
		}
		return 0;
	}
	

} // end namespace
} // end namespace
