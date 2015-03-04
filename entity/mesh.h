//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 31 March 2008 7:20:37 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __MESH_ENTITY_H_70D91D70_EB5E_4162_8988_35187F2D6FF6_
#define __MESH_ENTITY_H_70D91D70_EB5E_4162_8988_35187F2D6FF6_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine_abi.h"
#include "engine/entity/entity.h"
#include "engine/entity/render_interface.h"
#include "engine/object_model/object_type_info.h"
#include "engine/object_model/object_manager.h"
#include "graphics/shader/forward_decls.h"
#include "graphics/shader/parameter_buffer_view.h"
#include "graphics/shader/shader.h"
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
	/// simple static mesh
    class ENGINE_ABI mesh : 
		public entity_base,
		public entity::render_interface
    {
    public:
		typedef mesh this_type;

		/// constructor
		mesh(graphics::renderer_ptr r, const char *name);
		
		/// destructor
		~mesh();
		
		// entity interface
		virtual entity::render_interface* get_render_interface() { return this; }
		
		// render_interface
		virtual void render(graphics::renderer_ptr, graphics::camera_ptr camera);
		
		/// set the vertex range to render with
		void set_vertex_range(int first_vertex, int num_vertices);
		
		/// set the index range to render with
		void set_index_range(int first_index, int num_indicies);
		
		// accessors
		void set_mesh(const graphics::mesh_ptr &);
		graphics::shader::parameter_buffer_view set_shader(graphics::shader::shader_base_ptr);		
		void set_world_mat(const math::matrix4x4f &);
		graphics::mesh_ptr&	get_mesh();
		graphics::shader::shader_base_ptr get_shader();
				        
		/// \returns A view to the shader parameters this mesh is using
		graphics::shader::parameter_buffer_view get_shader_param_view();
		
    private:
		TYCHO_INTRUSIVE_PTR_FRIEND_DECLS(ENGINE_ABI, mesh)

		math::matrix4x4f							m_transform;	///< world transform for this mesh
		graphics::mesh_ptr							m_mesh;
		graphics::render_op_ptr						m_render_op;
		graphics::shader::shader_base_ptr			m_shader;
		graphics::shader::parameter_buffer_ptr		m_shader_params;
		graphics::shader::parameter_bindings_ptr	m_shader_bindings;
		graphics::shader::parameter_buffer_ptr		  m_mesh_params;
		graphics::shader::parameter_buffer_layout_ptr m_mesh_params_layout;
    };

	TYCHO_INTRUSIVE_PTR_FUNC_DECLS(ENGINE_ABI, mesh)

} // end namespace
} // end namespace
} // end namespace

#endif // __MESH_ENTITY_H_70D91D70_EB5E_4162_8988_35187F2D6FF6_
