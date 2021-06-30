#pragma once

namespace gfx
{

	class RenderObject
	{
	public:

		RenderObject(uint count, const float* const vertices, 
			const std::initializer_list<uint>& list) :
			m_VertexArray(count, vertices, list),
			m_IndexBuffer(m_VertexArray)
		{}
		RenderObject(const RenderObject& other) = delete;
		RenderObject(RenderObject&& other) = delete;

		void Bind() const
		{
			m_VertexArray.Bind();
			m_IndexBuffer.Bind();
		}
		uint GetIndexCount() const
		{
			return m_IndexBuffer.getCount();
		}

	private:
		VertexArray m_VertexArray;
		IndexBuffer m_IndexBuffer;


	};

}
