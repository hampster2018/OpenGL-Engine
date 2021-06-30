#include "pch.h"

int main()
{

	gfx::OpenGLInstance gl = gfx::init(800, 600, "Title", { .clear = {.b = 1.f} });

	float vertices[] =
		{
			-.5f, -.5f, 1.f, .25f, 0.f,
			.5f,  -.5f, 1.f, .25f, 0.f,
			.5f,  .5f,  1.f, .25f, 0.f,
			-.5f, .5f,  1.f, .25f, 0.f
		};

	gfx::RenderObject ro(math::arrlen(vertices), vertices, { 2, 3 });

	// 4 - Vertex Shader - Fragment Shader

	uint vertex = glCreateShader(GL_VERTEX_SHADER);
	uint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	gfx::Renderer renderer("res/shader.glsl");

	float offset = .0f, increment = .0005f;

	while (gl.IsRunning())
	{
		renderer.Clear();

		ro.Bind();

		if (math::abs(offset) >= 1.f)
		{
			increment *= -1;
		}
		offset += increment;
		renderer.GetShader().SetUniform2f("u_Camera", offset, offset);

		renderer.Draw(ro);
		renderer.Render(gl);
	}

	gfx::end(gl);
	return 0;
}