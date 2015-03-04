//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 1 April 2008 12:18:31 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __CAMERA_ENTITY_H_8166ECE8_E6F1_4AEC_84BE_58DFAD7FA08C_
#define __CAMERA_ENTITY_H_8166ECE8_E6F1_4AEC_84BE_58DFAD7FA08C_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "engine/entity/entity.h"
#include "math/matrix4x4.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace engine
{
namespace entity
{

    class ENGINE_ABI camera : public entity_base
    {
    public:
		typedef camera this_type;

		/// Constructor
		camera(const char *name);
		
		/// set the cameras view matrix
		void set_view_matrix(const math::matrix4x4f &);

		/// set the cameras projection matrix
		void set_projection_matrix(const math::matrix4x4f &);

		/// \returns the cameras view matrix
		const math::matrix4x4f& get_view_matrix();

		/// \returns the cameras projection matrix
		const math::matrix4x4f& get_projection_matrix();				
				
// 		/// Set the field of view for the camera
// 		/// \param fov Field of view in radians
// 		camera& set_fov(float fov);
// 		
// 		/// Set the aspect ratio for the camera
// 		camera& set_aspect_ratio(float aspect_ratio);
// 		
// 		/// Set the near and far clip plane distances
// 		camera& set_clip_planes(float near_clip, float far_clip);
// 		
// 		/// \returns The field of view
// 		float get_fov() const;
// 
// 		/// \returns The aspect ratio
// 		float get_aspect_ratio() const;
// 
// 		/// \returns The distance to the near clip plane
// 		float get_near_clip() const;
// 
// 		/// \returns The distance to the far clip plane
// 		float get_far_clip() const;
		
    private:
		TYCHO_INTRUSIVE_PTR_FRIEND_DECLS(ENGINE_ABI, camera)
		
// 		float m_fov;
// 		float m_aspect_ratio;
// 		float m_near_clip;
// 		float m_far_clip;
 		bool  m_dirty;
		math::matrix4x4f m_view_mat; ///< view matrix
		math::matrix4x4f m_proj_mat; ///< projection matrix
		math::matrix4x4f m_view_proj_mat; ///< view * projection matrix
    };
    
    TYCHO_INTRUSIVE_PTR_FUNC_DECLS(ENGINE_ABI, camera)

} // end namespace

} // end namespace

} // end namespace

#endif // __CAMERA_ENTITY_H_8166ECE8_E6F1_4AEC_84BE_58DFAD7FA08C_
