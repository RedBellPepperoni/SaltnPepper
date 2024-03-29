#ifndef MESH_H
#define MESH_H

#include "Engine/Core/Rendering/Buffers/VertexBuffer.h"
#include "Engine/Core/Rendering/Buffers/IndexBuffer.h"
#include "Engine/Core/Memory/MemoryDefinitions.h"

#include "Engine/Core/Rendering/RenderDefinitions.h"
#include <vector>
#include <string>

namespace SaltnPepperEngine
{
	class BoundingBox;

    namespace Rendering
    {
		class Material;

		class Mesh
		{

		protected:

			std::string m_meshName;

			// Storage for vertices and indicies for the Mesh
			std::vector<Vertex> m_vertices;
			std::vector<uint32_t> m_indicies;

			// The Buffers that are needed for OpenGL
			SharedPtr<VertexBuffer> m_VBO;
			SharedPtr<IndexBuffer> m_IBO;


			uint32_t m_vertexCount;
			uint32_t m_indiciesCount;

			// Material Stuuff

			bool m_isSkinned = false;

			SharedPtr<Material> m_material;
			SharedPtr<BoundingBox> m_boundingBox;

		public:

			Mesh();
			//Mesh(const Mesh& mesh);
			Mesh(const std::vector<Vertex>& inVertices, const std::vector<uint32_t>& inIndicies);

			~Mesh();

			// Change/Set the name of a mesh
			void SetName(const std::string& newName);

			// Getter for accessing the mesh's name
			const std::string& GetName() const;

			const bool GetSkinned() const { return m_isSkinned; }
			void SetSkinned(const bool value) { m_isSkinned = value; }

			// Getters for Vertex and Index data
			const std::vector<Vertex>& GetVertexData();
			const std::vector<uint32_t>& GetIndexData();

			/*std::vector<Vertex>& GetVertexData();
			std::vector<uint32_t>& GetIndexData();*/

			void SetVertexData(const std::vector<Vertex> newVertexData);

			const uint32_t GetIndexCount() const;
			const uint32_t GetVertexCount() const;

			// Getters for Vertex and Index buffers
			SharedPtr<VertexBuffer>& GetVBO();
			SharedPtr<IndexBuffer>& GetIBO();

			void SetMaterial(const SharedPtr<Material>& newMaterial);
			SharedPtr<Material>& GetMaterial();
 
			const SharedPtr<BoundingBox>& GetBoundingBox();

			static void RecalculateNormals(std::vector<Vertex>& vertices,const std::vector<uint32_t>& indices);

		};
    }
}


#endif // !MESH_H
