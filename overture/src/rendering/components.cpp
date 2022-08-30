#include "components.h"

Mesh::Mesh(std::vector<renderer::PosTexColor> verticies, std::vector<uint32_t> indices) {
	vertexArray = new gl::VertexArray();
	vertexBuffer = new gl::VertexBuffer(verticies.data(), verticies.size() * sizeof(renderer::PosTexColor));
	indexBuffer = new gl::IndexBuffer(indices.data(), indices.size());
	gl::BufferLayout layout = {
		{gl::ShaderDataType::Float3, "aPos"},
		{gl::ShaderDataType::Float3, "aColor"},
		{gl::ShaderDataType::Float2, "aTextCoord"}
	};
	vertexBuffer->setLayout(layout);
	vertexArray->addVertexBuffer(*vertexBuffer);

	vertexArray->setIndexBuffer(*indexBuffer);
}
