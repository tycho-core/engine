//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 31 March 2008 7:20:37 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "mesh.h"
#include "graphics/renderer.h"
#include "graphics/render_op.h"
#include "graphics/texture.h"
#include "graphics/vertex_buffer.h"
#include "graphics/index_buffer.h"
#include "graphics/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader/parameter_bindings.h"
#include "graphics/shader/parameter_buffer_layout.h"
#include "graphics/shader/parameter_buffer.h"
#include "graphics/shader/parameter_object_lookup_table.h"
#include "graphics/shader/parameters.h"
#include "core/colour/rgba.h"
#include "math/matrix3x4.h"
#include "math/matrix4x4.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
using namespace tycho::engine;
using namespace tycho::graphics;
using namespace tycho::graphics::shader;

namespace tycho
{
namespace engine
{
namespace entity
{
	TYCHO_INTRUSIVE_PTR_FUNC_IMPL(ENGINE_ABI, mesh)

	/// constructor
	mesh::mesh(graphics::renderer_ptr renderer, const char *name) : 
		entity_base(name),
		m_transform(math::matrix4x4f::create_identity()),
		m_shader_bindings(new graphics::shader::parameter_bindings())
	{
		// expose our parameters
		m_mesh_params_layout = parameter_buffer_layout_ptr(new parameter_buffer_layout());
		m_mesh_params_layout->add_parameter("colour", spt_float4, spm_none);
		m_mesh_params_layout->add_parameter("world_matrix", spt_matrix44, spm_none);
		m_mesh_params_layout->finalise();
		m_mesh_params = parameter_buffer_ptr(new parameter_buffer(m_mesh_params_layout->get_required_size()));		
		graphics::shader::parameter_buffer_view view(m_mesh_params, m_mesh_params_layout);
		view.set<math::matrix4x4f>("world_matrix", math::matrix4x4f::create_identity());
		
		// default shader bindings
		m_shader_bindings->bind("view_proj", "camera", "view_proj_matrix");		
		m_shader_bindings->bind("world_matrix", "mesh", "world_matrix");
		//m_shader_bindings->bind("obj_clr", "mesh", "obj_clr");				

		// setup render operation for this mesh
		m_render_op = renderer->create_render_op();
		m_render_op->first_vertex	= 0;
		m_render_op->first_index	= 0;
		m_render_op->primitive		= primitive_type_tri_list;
	}

	/// destructor
	mesh::~mesh()
	{	
	}

	// render_interface
	void mesh::render(graphics::renderer_ptr r, graphics::camera_ptr camera)
	{
		using namespace graphics;
				
		// bind shader parameters for this call
		scoped_parameter_object mesh_params(camera->get_parameter_object_lookup_table(), "mesh",  
										    parameter_buffer_view(m_mesh_params, m_mesh_params_layout));
										    
		m_shader->bind(m_shader_params, camera->get_parameter_object_lookup_table(), m_shader_bindings);
		r->render(m_render_op);
	}

	void mesh::set_mesh(const graphics::mesh_ptr &m)
	{
		m_mesh = m;
		m_render_op->num_vertices	= m_mesh->m_vb->get_num_verts();
		m_render_op->num_indices	= m_mesh->m_ib->get_num_indices();
		m_render_op->vertex_buffers[0] = m_mesh->m_vb;
		m_render_op->index_buffers[0]  = m_mesh->m_ib;			
	}
	
	graphics::shader::parameter_buffer_view mesh::set_shader(graphics::shader::shader_base_ptr s)
	{
		m_shader = s;
		m_shader_params = m_shader->create_default_table();
		m_render_op->shader			= m_shader;		
		m_render_op->shader_params  = m_shader_params;
		return graphics::shader::parameter_buffer_view(m_shader_params, m_shader->get_parameter_layout());
	}
	
	void mesh::set_world_mat(const math::matrix4x4f &mat)
	{
		graphics::shader::parameter_buffer_view view(m_mesh_params, m_mesh_params_layout);
		view.set<math::matrix4x4f>("world_matrix", mat);
	}
	
	graphics::mesh_ptr& mesh::get_mesh()
	{
		return m_mesh;
	}
	
	graphics::shader::shader_base_ptr mesh::get_shader()
	{
		return m_shader;
	}

	graphics::shader::parameter_buffer_view mesh::get_shader_param_view()
	{
		return graphics::shader::parameter_buffer_view(m_shader_params, m_shader->get_parameter_layout());
	}

	void mesh::set_vertex_range(int first_vertex, int num_vertices)
	{
		m_render_op->first_vertex = first_vertex;
		m_render_op->num_vertices = num_vertices;
	}
	
	void mesh::set_index_range(int first_index, int num_indices)
	{
		m_render_op->first_index = first_index;
		m_render_op->num_indices = num_indices;
	}

} // end namespace
} // end namespace
} // end namespace
