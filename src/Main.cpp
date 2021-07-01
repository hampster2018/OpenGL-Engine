#include "pch.h"

int main()
{

	gfx::OpenGLInstance gl = gfx::init(800, 600, "Title", { .clear = {.b = 1.f} });

	float vertices[] =
		{
			-.5f, -.5f, 0.f, 0.f, 0.f,
			.5f,  -.5f, 1.f, 0.f, 0.f,
			.5f,  .5f, 1.f, 1.f, 0.f,
			-.5f, .5f, 0.f, 1.f, 0.f
		};

	gfx::RenderObject ro(math::arrlen(vertices), vertices, { 2, 2, 1 });

	// 4 - Vertex Shader - Fragment Shader

	uint vertex = glCreateShader(GL_VERTEX_SHADER);
	uint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	gfx::Renderer renderer("res/shader_Texture.glsl");

	uint textureUnits = gfx::GetMaxTextureUnits();
	printf("%d\n", textureUnits);
	int* samplers = new int[textureUnits];

	for (uint i = 0; i < textureUnits; i++)
		samplers[i] = i;
	renderer.GetShader().SetUniform1iv("u_Textures", textureUnits, samplers);

	for (uint i = 0; i < textureUnits; i++)
		samplers[i] = 0;
	renderer.GetShader().SetUniform1iv("u_TextureFrames", textureUnits, samplers);

	constexpr uint dataWidth = 16, dataHeight = 16, dataFrames = 2;
	constexpr uint dataFrameSize = dataWidth * dataHeight * 4,
		dataSize = dataFrameSize * dataFrames;

	uchar data[dataSize] = { 0 };
	for (uint i = 0; i < dataWidth * dataHeight; i++)
	{
		data[i * 4 + 0] = 255;
		data[i * 4 + 3] = 255;
		data[dataFrameSize + i * 4 + 1] = 255;
		data[dataFrameSize + i * 4 + 3] = 255;
	}
	gfx::Texture tex(data, dataWidth, dataHeight, dataFrames, {.min = GL_NEAREST, .mag = GL_NEAREST});

	float offset = .0f, increment = .0005f;

	double updateTime = 0;
	int frame = 0;
	while (gl.IsRunning())
	{
		renderer.Clear();

		ro.Bind();

		double time = glfwGetTime();
		if (time - updateTime > .5)
		{
			samplers[0] = frame;
			frame = (frame + 1) % dataFrames;
			renderer.GetShader().SetUniform1iv("u_TextureFrames", textureUnits, samplers);
			updateTime = time;
		}

		renderer.Draw(ro);
		renderer.Render(gl);
	}

	delete[] samplers;
	gfx::end(gl);
	return 0;
}