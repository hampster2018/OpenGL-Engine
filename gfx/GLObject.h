#pragma once


namespace gfx
{
	class GLObject
	{
	public:

		GLObject() : m_Id(0) {}
		GLObject(const GLObject& other) = delete;
		GLObject(GLObject&& other) = delete;
		virtual ~GLObject() {};


		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		uint getId()
		{
			return m_Id;
		}

	protected:

		uint m_Id;


	};
}