//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:28:27 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "text_input_archive.h"
#include "archive.h"
#include "object_model.h"
#include "core/string.h"
#include "core/debug/assert.h"
#include <string.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
using namespace tycho::core;

namespace tycho
{
namespace engine
{

	namespace detail
	{			
		int64 to_int64(const char *str)
		{
			return tycho::core::atoi(str);
		}

		int32 to_int32(const char *str)
		{
			return tycho::core::atoi(str);
		}
		
		float64 to_float64(const char *str)
		{
			return tycho::core::atof(str);
		}

		float32 to_float32(const char *str)
		{
			return (float32)tycho::core::atof(str);
		}
	
	} // end namespace
	
	text_input_archive::text_input_archive(reactor *r) :
		m_reactor(r)
	{	
	}
	
	struct string_reader
	{
		string_reader(char *ptr, int /*len*/, char sep) :
            m_sep(sep),
			m_cur(0),
            m_next(0)
		{
			if(ptr && *ptr)
			{
				m_cur = ptr;
				m_next = null_terminate_string(m_cur);
			}					
		}
		
		char* get_next_string()
		{
			char *cur = m_cur;
			m_cur = m_next;
			m_next = null_terminate_string(m_cur);
			return cur;
		}
		
		/// finds the beginning of the next string and null terminates the current string,
		/// \returns pointer to next string or 0 if at the end
		char* null_terminate_string(char *ptr)
		{
			if(!ptr)
				return 0;
			while(*ptr && *ptr != m_sep)
			{
				++ptr;
			}
			if(*ptr)
			{
				*ptr++ = 0;
				// step over all whitespace to next string
				while(*ptr && *ptr <= m_sep)
				{
					++ptr;
				}
				
				if(*ptr)
					return ptr;
			}
			return 0;
		}
	
	private:
		char  m_sep;
		char *m_cur;
		char *m_next;
	};
	
	
	/// parse a buffer of text, this must be newline terminated
	void text_input_archive::parse(char *ptr, int len)		
	{
		m_reactor->parse_begin();
		
		// process a line at a time
		string_reader line_reader(ptr, len, '\n');
		for(char *p = line_reader.get_next_string(); p; p = line_reader.get_next_string() )
		{
			if(*p == '#')
			{
				// control statement
				++p;				
				if(core::strncmp(p, "bo", 2) == 0)
				{
					p += 3;
					string_reader sr(p, 0, ' ');						
					const char *type = sr.get_next_string();
					const char *name = sr.get_next_string();
					const char *version = sr.get_next_string();
					TYCHO_ASSERT(name);
					TYCHO_ASSERT(type);
					m_reactor->begin_object(type, name, detail::to_int32(version));
				}
				else if(core::strncmp(p, "eo", 2) == 0)
				{
					m_reactor->end_object();
				}		
				else if(core::strncmp(p, "ba", 2) == 0)					
				{
					const char *name = 0;
					const char *type = 0;
					m_reactor->begin_array(name, type);
				}
				else if(core::strncmp(p, "ea", 2) == 0)					
				{
					m_reactor->end_array();
				}
				else if(core::strncmp(p, "bb", 2) == 0)
				{
					p += 3;
					string_reader sr(p, 0, ' ');						
					const char *type = sr.get_next_string();
					const char *version = sr.get_next_string();
					TYCHO_ASSERT(type);
					m_reactor->begin_base_class(type, detail::to_int32(version));						
				}
				else if(core::strncmp(p, "eb", 2) == 0)					
				{
					m_reactor->end_base_class();
				}
			}		
			else
			{
				// data declaration
				string_reader sr(p, 0, ' ');						
				const char *name = sr.get_next_string();
				const char *type = sr.get_next_string();
				const char *val  = sr.get_next_string();
				TYCHO_ASSERT(name);
				TYCHO_ASSERT(type);
				TYCHO_ASSERT(val);
				member_type mt = from_string(type);
				member_value mv;
				mv.type = from_string(type);
				if(mt)
				{
					switch(mt)
					{
						case vt_int8	: mv.value.i8 = (int8)detail::to_int64(val); break;
						case vt_uint8	: mv.value.ui8 = (uint8)detail::to_int64(val); break;
						case vt_int16	: mv.value.i16 = (int16)detail::to_int64(val); break;
						case vt_uint16	: mv.value.ui16 = (uint16)detail::to_int64(val); break;
						case vt_int32	: mv.value.i32 = (int32)detail::to_int32(val); break;
						case vt_uint32	: mv.value.ui32 = (uint32)detail::to_int64(val); break;
						case vt_float32	: mv.value.f32 = detail::to_float32(val); break;
						case vt_string	: mv.value.str = val; break;
						case vt_object	: mv.value.str = val; break;
						case vt_bool	: mv.value.i32 = (int32)detail::to_int64(val); break;
						case vt_float64	: mv.value.f64 = detail::to_float64(val); break;
						case vt_int64	: mv.value.i64 = detail::to_int64(val); break;
						case vt_uint64	: mv.value.ui64 = detail::to_int64(val); break;
                            
                        default: TYCHO_NOT_IMPLEMENTED; break;
					}
					
					m_reactor->read_member(name, mv);
				}
			}				
		} 		
		m_reactor->parse_end();			
	}		

} // end namespace
} // end namespace
