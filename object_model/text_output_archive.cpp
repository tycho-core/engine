//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 1:28:16 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "text_output_archive.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace engine
{

	text_output_archive::text_output_archive(std::ostream &ostr) : 
		m_ostr(ostr)
	{
	}

	void text_output_archive::begin_object(const char *type, const char *name, int version)
	{
		m_ostr << "#bo " << type << " " << name << " " << version << "\n";
	}
	
	void text_output_archive::end_object()
	{
		m_ostr << "#eo\n";	
	}

	void text_output_archive::begin_base_class(const char *type, int version)
	{
		m_ostr << "#bb " << type << " " << version << "\n";
	}
	
	void text_output_archive::end_base_class()
	{
		m_ostr << "#eb\n";	
	}
	
	void text_output_archive::begin_array(const char *type, const char *name)
	{
		m_ostr << "#ba " << type << " " << name << "\n";;
	}
	
	void text_output_archive::end_array()
	{
		m_ostr << "#ea\n";
	}
	
	void text_output_archive::write(const char *name, const char *type, char c)
	{
		m_ostr << name << " " << type << " " << c << "\n";
	}
	
	void text_output_archive::write(const char *name, const char *type, int i)
	{
		m_ostr << name << " " << type << " " << i << "\n";
	}

	void text_output_archive::write(const char *name, const char *type, core::int64 i)
	{
		m_ostr << name << " " << type << " " << i << "\n";
	}

	void text_output_archive::write(const char *name, const char *type, core::uint64 i)
	{
		m_ostr << name << " " << type << " " << i << "\n";
	}

	void text_output_archive::write(const char *name, const char *type, float f)
	{
		/// \todo  deal with float precision issues, i.e. use hex or write with as many digits as necessary
		m_ostr << name << " " << type << " " << f << "\n";
	}
	
	void text_output_archive::write(const char *name, const char *type, double d)
	{
		/// \todo  deal with float precision issues, i.e. use hex or write with as many digits as necessary
		m_ostr << name << " " << type << " " << d << "\n";
	}

	void text_output_archive::write(const char *name, const char *type, unsigned char c)
	{
		m_ostr << name << " " << type << " " << c << "\n";
	}
	
	void text_output_archive::write(const char *name, const char *type, unsigned int i)
	{
		m_ostr << name << " " << type << " " << i << "\n";
	}

	void text_output_archive::write(const char *name, const char *type, const char *str)
	{
		/// \todo  escape
		m_ostr << name << " " << type << " " << (str ? str : "0") << "\n";
	}
	

} // end namespace
} // end namespace
