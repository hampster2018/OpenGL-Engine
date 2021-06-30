#pragma once

namespace gfx
{

	class VertexArray : public GLObject
	{
	public:
		VertexArray(uint count, const float* const vertices, const std::initializer_list<uint>& list) :
			m_Buffer(count, vertices),
			m_VertexSize(std::reduce(list.begin(), list.end(), 0, std::plus<uint>()))
		{
			glGenVertexArrays(1, &m_Id);
			printf("Create VA %u\n", m_Id);

			Bind();
			m_Buffer.Bind();
			
			const uint stride = m_VertexSize * sizeof(float);
			uint offset = 0, i = 0;
			for (uint n : list)
			{
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, n, GL_FLOAT, GL_FALSE, stride, (const void*)(offset * sizeof(float)));
				offset += n;
				i++;
			}
		}

		VertexArray(const VertexArray& other) = delete;
		VertexArray(VertexArray&& other) = delete;
		~VertexArray()
		{
			printf("Delete VA %u\n", m_Id);
			glDeleteVertexArrays(1, &m_Id);
		}

		void Bind() const override
		{
			glBindVertexArray(m_Id);
		}
		void Unbind() const override
		{
			glBindVertexArray(0);
		}
		uint GetVertexCount() const
		{
			return m_Buffer.getCount() / m_VertexSize;
		}

	private:
		VertexBuffer m_Buffer;
		uint m_VertexSize;
		

	};
}