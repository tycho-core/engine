//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:23:41 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __OBJECT_TYPE_INFO_H_E53CB5C3_3E51_432F_99C3_C3275A7EA054_
#define __OBJECT_TYPE_INFO_H_E53CB5C3_3E51_432F_99C3_C3275A7EA054_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "object_model.h"
#include <vector>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// MACROS
//////////////////////////////////////////////////////////////////////////////

#define OBJECT_INTERFACE(_type) \
	static tycho::engine::object_type_info* ms_type_info; \
	virtual const tycho::engine::object_type_info* get_type_info() const { return ms_type_info; } \
	virtual void*	most_derived_ptr() { return this; } \
	static tycho::engine::object* create(const char *name) { return new _type(name); }
	
#define REGISTER_TYPE_HEADER(_name) \
	static tycho::engine::object_type_info* register_type() {

#define REGISTER_TYPE_FOOTER } 

#define REGISTER_TYPE(_name, _version) \
	OBJECT_INTERFACE(_name) \
	REGISTER_TYPE_HEADER(_name) \
	typedef _name this_type; \
	tycho::engine::object_type_info *ti = new tycho::engine::object_type_info(#_name, _version, &_name::create);

#define REGISTER_TYPE_END()	\
	tycho::engine::object_manager::register_type(ti); \
	this_type::ms_type_info = ti; \
	return ti; \
	REGISTER_TYPE_FOOTER
	
#define REGISTER_MEMBER(_name, _type)  { \
	tycho::engine::object_member *om = new tycho::engine::object_member(); \
	om->m_name = #_name; \
	om->m_type = _type; \
	om->m_offset = offsetof(this_type, _name); \
	ti->add_member(om); } 
	
#define REGISTER_MEMBER_2(_class, _name, _type, _load_func, _save_func) \
	tycho::engine::object_member *om = new tycho::engine::object_member(); \
	om->m_name = #_name; \
	om->m_type = _type; \
	om->m_offset = offsetof(_class, _name); \
	ti->add_member(om); } 
	
#define REGISTER_LEGACY_LOADER(_fn) \
	ti->set_legacy_loader_func(_fn);
	
// #define REGISTER_BASE(_base, _class) \
// 	_class *c = (_class*)(0x3ffffff); \
// 	_base *b = static_cast<_base*>(c);	\
// 	int fixup = (int)(c) - (int)(b); \
// 	ti->add_base_class(_base::ms_type_info, fixup); 

#define REGISTER_BASE(_base)

 #define IMPLEMENT_TYPE(_type)	 \
 	tycho::engine::object_type_info* _type::ms_type_info = _type::register_type();
//#define IMPLEMENT_TYPE(_type)	 \
//	tycho::engine::object_type_info* _type::ms_type_info;


//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
	class object;
	class object_archive_reader;
	
	/// information about a single member variable of an object.
	class ENGINE_ABI object_member
	{
	public:
		std::string m_name;
		member_type m_type;
		int			m_offset;
	};
	
	typedef object* (*object_create_func)(const char*);
	typedef object* (*legacy_loader_func)(object_archive_reader*, int version);

    class ENGINE_ABI object_type_info
    {
    public:
		struct base_class
		{
			const object_type_info *ti;
			int ptr_fixup;
		};

	public:        
		/// constructor
		object_type_info(const char *name, int version, object_create_func create_func);
		
		/// destructor
		~object_type_info();
		
		/// set legacy version loader
		void set_legacy_loader_func(legacy_loader_func f);
		
		/// call the function to handle legacy versions of this type
		void call_legacy_loader_func(object_archive_reader *, int version);
		
		/// create a new instance of this object        
		object* create_object(const char *name) const;	
		
		/// \returns the version of this type
		int get_version() const
			{ return m_version; }
			
		/// \returns the full name of this object
		const char* get_name() const
			{ return m_name.c_str(); }

		/// add a member to the type. it takes ownership of the pointer.
		void add_member(object_member *om) 
			{ m_members.push_back(om);}
		
		/// \returns the number of members in this object
		size_t num_members() const
			{ return m_members.size(); }
			
		/// \returns the i'th member in this object
		const object_member* get_member(size_t i) const
			{ return m_members[i]; }
			
		/// lookup a member index by name
		const object_member* lookup_member(const char *name) const;

		/// lookup a member base class by name
		const base_class* lookup_base_class(const char *name) const;
			
		/// add a base class
		void add_base_class(const object_type_info *base, int fixup);
		
		///\returns number of base classes this type has
		size_t num_base_classes() const
			{ return m_base_classes.size(); }

		///\returns the i'th base class
		const object_type_info* get_base_class(size_t i) const
			{ return m_base_classes[i].ti; }
			
		/// cast the pointer of this type to that of a base class type
		void* cast(void *ptr, const object_type_info *ti) const;
						
		/// \name Functions
		//@{							
			/// add a function to the class
			struct param_info;
			struct member_function;
			void add_function(const char* name, int num_params, param_info*);
		
			/// call the specified function on the passed object
			bool call_function(object*, member_function*, param_info* );								
			
		//@}
		
    private:
		typedef std::vector<object_member*> member_list;
		typedef std::vector<base_class> base_class_list;

		object_create_func m_create_func;
		legacy_loader_func m_legacy_loader_func;
		std::string		m_name;
		core::int32		m_version;
		member_list		m_members;						
		base_class_list m_base_classes;	///< possibly multiple base classes of this object
    };

	
} // end namespace
} // end namespace

#endif // __OBJECT_TYPE_INFO_H_E53CB5C3_3E51_432F_99C3_C3275A7EA054_
