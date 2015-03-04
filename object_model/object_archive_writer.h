//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 5 March 2008 8:10:17 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __OBJECT_ARCHIVE_WRITER_H_78404DB8_4D21_487D_88DB_CC7C0BE3A58F_
#define __OBJECT_ARCHIVE_WRITER_H_78404DB8_4D21_487D_88DB_CC7C0BE3A58F_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
	class archive;
	class object;
	class object_type_info;
	
    class ENGINE_ABI object_archive_writer
    {
    public:
		/// constructor
		object_archive_writer(archive *output_archive);
		
		/// write entire object tree to the archive
		void write(object *root);

	private:
		void write_object(void *obj, const object_type_info *ti, bool is_base);
		
    private:
		archive* m_output_archive;
    };

} // end namespace
} // end namespace

#endif // __OBJECT_ARCHIVE_WRITER_H_78404DB8_4D21_487D_88DB_CC7C0BE3A58F_
