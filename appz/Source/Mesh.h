#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "Vertex.h"
#include "Mtx44.h"
#include "GL\glew.h"
#include "Material.h"
#include "Voxel.h"

/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	Mesh(const std::wstring &meshName, std::vector<Vertex>& Vertex_buffer);
	~Mesh();
	const std::wstring& GetName() const;
	void Render( unsigned textureID = 0, unsigned mode = GL_TRIANGLES);
	//a function made to render only parts of the mesh
	void Render(unsigned offset, unsigned count, unsigned textureID, unsigned mode);
	std::vector<Voxel> GenerateVoxels();
private:
	const std::wstring name;
	unsigned m_vertexBuffer;
	std::vector<Vertex> vertices;
	Material material;
	int nVerts;
};

#endif