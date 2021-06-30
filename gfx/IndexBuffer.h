#pragma once


namespace gfx
{

	class IndexBuffer : public Buffer<GL_ELEMENT_ARRAY_BUFFER>
	{
	public:
		IndexBuffer(const VertexArray& va) :
			Buffer<GL_ELEMENT_ARRAY_BUFFER>(va.GetVertexCount() * 6 / 4)
		{
			printf("Create IB %u\n", m_Id);

			uint* temp = new uint[m_Count];
			for (uint i = 0; i < m_Count; i++)
				temp[i] = s_Offsets[i % 6] + i/6 * 4;

			Write(m_Count * sizeof(float), temp);
			delete[] temp;
		}
		IndexBuffer(const IndexBuffer& other) = delete;
		IndexBuffer(IndexBuffer&& other) = delete;
		~IndexBuffer()
		{
			printf("Delete IB %u\n", m_Id);
		}

	private:
		constexpr static uint s_Offsets[] = { 0, 1, 2, 0, 2, 3 };

	};


}