//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:48:49 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __OBJECT_ARCHIVE_READER_H_B52FD187_0DCE_4B08_84CE_1CA8C4EB866C_
#define __OBJECT_ARCHIVE_READER_H_B52FD187_0DCE_4B08_84CE_1CA8C4EB866C_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "archive.h"
#include "text_input_archive.h"
#include <map>
#include <vector>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
	class object;
	class object_member;
	class object_type_info;
	
	/// object factory archive reactor, this is responsible for the
	/// actual creation of objects and setting of data members in 
	/// response to events emitted by the parser.
    class ENGINE_ABI object_archive_reader : public text_input_archive::reactor
    {
	public:
		object_archive_reader();
		
		virtual void parse_begin();
		virtual void parse_end();
		virtual void begin_object(const char *type, const char *name, int version);
		virtual void end_object();
		virtual void begin_base_class(const char *type, int version);
		virtual void end_base_class();
		virtual void begin_array(const char *type, const char *name);
		virtual void end_array();
		virtual void read_member(const char* name, member_value value);
		
		object* get_root() { return m_root; }
		
	private:
		object* m_cur_obj;
		object* m_root;
		void*	m_cur_base;
		const object_type_info *m_cur_base_type;
		
		struct object_link
		{
			std::string name;
			object *obj;
		
			object_link() : obj(0) {}	
			struct link
			{
				object *o;
				const object_member *om;
			};
			
			std::vector<link> links;
		};
		
		typedef std::map<std::string, object_link> object_link_map;
		object_link_map m_object_links;
	};

} // end namespace
} // end namespace

#endif // __OBJECT_ARCHIVE_READER_H_B52FD187_0DCE_4B08_84CE_1CA8C4EB866C_
