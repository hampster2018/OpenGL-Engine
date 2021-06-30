#pragma once


namespace gfx
{

	template<GLenum TARGET>
	class Buffer : public GLObject
	{
	public:

		void Bind() const override
		{
			glBindBuffer(TARGET, m_Id);
		}
		void Unbind() const override
		{
			glBindBuffer(TARGET, 0);
		}
		uint getCount() const
		{
			return m_Count;
		}

	protected:

		uint m_Count;


		Buffer(uint count) :
			m_Count(count)
		{
			glGenBuffers(1, &m_Id);
		}
		Buffer(const Buffer& other) = delete;
		Buffer(Buffer&& other) = delete;
		virtual ~Buffer()
		{
			glDeleteBuffers(1, &m_Id);
		}
		

		template<typename T>
		void Write(uint size, const T* data)
		{
			Bind();
			glBufferData(TARGET, size, data, GL_STATIC_DRAW);
		}

	};
}