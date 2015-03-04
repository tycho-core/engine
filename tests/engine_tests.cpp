//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Sunday, 27 April 2008 11:42:40 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "engine/engine.h"
#include "engine/globals.h"
#include "core/core.h"
#include "core/file_utils.h"
#include "core/debug/assert.h"
#include "core/memory/new.h"
#include "core/globals.h"
#include "core/string.h"
#include "core/io/types.h"
#include "core/io/file_stream.h"
#include "core/io/interface.h"
#include <iostream>
#include <fstream>
 
using namespace tycho;
 
namespace te = tycho::engine;
namespace tc = tycho::core; 


namespace tycho
{
namespace engine
{
namespace tests
{

int test_shader_parameters()
{
// 	parameter_buffer* buffer = m_shader->create_default_table();
// 	parameter_buffer_layout* buffer_layout = m_shader->get_parameter_layout();
// 	parameter_buffer_view param_view(buffer, buffer_layout);
// 	param_view.set<core::rgba>("foo", core::rgba(12,43,123));
// 	core::rgba clr = param_view.get<core::rgba>("foo");
// 	core::rgba* clr2 = param_view.get_ptr<core::rgba>("foo"); // get ptr, never look up again
// 	*clr2 = rgba(255,255,255,255);	
	return 0;
}

void test_ui_layout_file()
{
	// test button
	{
// 		core::io::file_stream s(core::globals::get_io().open_file("files/ui/button.ui", core::io::open_flag_read));
// 		TYCHO_ASSERT(!s.fail());
// 		std::vector<engine::ui::widget_ptr> widgets;
// 		TYCHO_ASSERT(engine::ui::load_layout(s, widgets));
//		TYCHO_ASSERT(widgets.size() == 1);
	};
}

} // end namespace
} // end namespace
} // end namespace

int main(int , char* [])
{	
	core::initialise();
	engine::initialise();
	
	using namespace tycho::engine::tests;
	engine::shutdown();
	core::shutdown();
	
	return 0;
}

	