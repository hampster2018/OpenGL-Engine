#pragma once

namespace gfx
{

	class Renderer
	{
	public:
		Renderer(const char* fp) :
			m_Shader(fp)
		{}
		Renderer(const Renderer& other) = delete;
		Renderer(Renderer&& other) = delete;
		
		void Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}
		void Draw(const RenderObject& obj) const
		{
			m_Shader.Bind();
			obj.Bind();
			glDrawElements(GL_TRIANGLES, obj.GetIndexCount(), 
				GL_UNSIGNED_INT, nullptr);
		}
		void Draw(const RenderObject& obj, const Texture& texture, const Shader& shader) const
		{
			obj.Bind();
			texture.Bind();
			shader.Bind();
			glDrawElements(GL_TRIANGLES, obj.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}
		void Render(const OpenGLInstance& gl) const
		{
			glfwSwapBuffers(gl.window);
			glfwPollEvents();
		}

		Shader& GetShader() const
		{
			return m_Shader;
		}

	private:
		mutable Shader m_Shader;
	};

}