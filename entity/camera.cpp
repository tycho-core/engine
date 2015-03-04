//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 1 April 2008 12:18:31 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "camera.h"


//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace engine
{
namespace entity
{
	TYCHO_INTRUSIVE_PTR_FUNC_IMPL(ENGINE_ABI, camera)

	/// Constructor
	camera::camera(const char *name) : 
		entity_base(name),		
		m_dirty(true)
	 {}
	
	/// set the cameras position
	void camera::set_view_matrix(const math::matrix4x4f &v)
	{
		m_view_mat = v;
 		m_dirty = true;			
// 		return *this;
	}
	
	/// set the cameras projection matrix
	void camera::set_projection_matrix(const math::matrix4x4f &v)
	{
		m_proj_mat = v;
	}

	/// \returns the cameras view matrix
	const math::matrix4x4f& camera::get_view_matrix()
	{
		return m_view_mat;
	}

	/// \returns the cameras projection matrix
	const math::matrix4x4f& camera::get_projection_matrix()
	{
		return m_proj_mat;
	}

} // end namespace
} // end namespace
} // end namespace
