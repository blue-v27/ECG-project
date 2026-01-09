#pragma once

class ShaderTypes
{
public:
	static constexpr char* waterVertex   = "Shaders/water_vertex_shader.glsl";
	static constexpr char* waterFragment = "Shaders/water_fragment_shader.glsl";

	static constexpr char* lineVertex   = "Shaders/line_vertex_shader.glsl";
	static constexpr char* lineFragment = "Shaders/line_fragment_shader.glsl";

	static constexpr char* textVertex   = "Shaders/text_vertex_shader.glsl";
	static constexpr char* textFragment = "Shaders/text_fragment_shader.glsl";

	static constexpr char* basicVertex   = "Shaders/vertex_shader.glsl";
	static constexpr char* basicFragment = "Shaders/fragment_shader.glsl";

	static constexpr char* sunVertex   = "Shaders/sun_vertex_shader.glsl";
	static constexpr char* sunFragment = "Shaders/sun_fragment_shader.glsl";

	static constexpr char* ghostVertex   = "Shaders/ghost_vertex_shader.glsl";
	static constexpr char* ghostFragment = "Shaders/ghost_fragment_shader.glsl";

	static constexpr char* skyVertex   = "Shaders/sky_vertex_shader.glsl";
	static constexpr char* skyFragment = "Shaders/sky_fragment_shader.glsl";
};