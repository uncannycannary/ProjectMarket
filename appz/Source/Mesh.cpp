
#include "Mesh.h"
#include "GL\glew.h"
#include "LoadTGA.h"

Mesh::Mesh(const std::wstring &meshName, std::vector<Vertex>& Vertex_buffer)
	:
name(meshName)
{
	nVerts = Vertex_buffer.size();
	vertices = Vertex_buffer;
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, Vertex_buffer.size() * sizeof(Vertex), &Vertex_buffer.front(), GL_STATIC_DRAW);\
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vertexBuffer);
}

const std::wstring& Mesh::GetName() const
{
	return name;
}

std::vector<Voxel> Mesh::GenerateVoxels()
{
	std::vector<Voxel> voxels;
	const float sizeOfVoxel = Voxel::GetSize();
	//create a buffer to store the vertices that were transformed by the matrix
	std::vector<Vertex> temp_vertices;
	temp_vertices = vertices;
	for(std::vector<Vertex>::iterator vertex = temp_vertices.begin(); vertex != temp_vertices.end();vertex+=3)
	{
		//create 2 vectors to represent the triangle
		Vector3 triangleVector1 = (vertex+1)->pos - vertex->pos;
		Vector3 triangleVector2 = (vertex+1)->pos - (vertex+2)->pos;
		Vector3 LongestVector;
		if(triangleVector1.Length() > triangleVector2.Length())
		{
			LongestVector = triangleVector1;
		}
		else
		{
			LongestVector = triangleVector2;
		}
		const unsigned steps = (LongestVector.Length() + 0.5) / sizeOfVoxel;
		for(Vector3 displacement1, displacement2, increment1 = triangleVector1 / steps, increment2 = triangleVector2 / steps; displacement1.Length() < triangleVector1.Length(); displacement1 += increment1, displacement2 += increment2)
		{
			//create a vector that we create our voxel in
			Vector3 point1 = vertex->pos + displacement1;
			Vector3 point2 = (vertex+2)->pos + displacement2;
			Vector3 voxelVector = point2 - point1;
			for(Vector3 displacement = voxelVector.Normalized() * (sizeOfVoxel*0.5), increment = voxelVector.Normalized() * sizeOfVoxel; displacement.Length() < voxelVector.Length(); displacement += increment)
			{
				Vector3 voxelPosition = point1 + displacement;

				//remove the floating point values
				voxelPosition.x = (int)voxelPosition.x;
				voxelPosition.y = (int)voxelPosition.y;
				voxelPosition.z = (int)voxelPosition.z;

				Voxel temp;
				temp.SetPositionTo(voxelPosition);
				temp.SetColorTo(Color());

				//check if the we already have similar voxel before adding it to the vector
				bool isUnique = true;
				for(std::vector<Voxel>::iterator voxel = voxels.begin(); voxel != voxels.end(); ++voxel)
				{
					if(*voxel == temp)
					{
						isUnique = false;
						break;
					}
				}
				if(isUnique)
				{
					voxels.push_back(temp);
				}
			}
		}
	}
	return voxels;
}

void Mesh::Render(unsigned textureID, unsigned mode)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Color)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Color) + sizeof(Vector3)));
	glDrawArrays(mode, 0, nVerts);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::Render(unsigned offset, unsigned count, unsigned textureID, unsigned mode)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Color)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Color) + sizeof(Vector3)));
	glDrawArrays(mode, offset, count);

	glBindTexture(GL_TEXTURE_2D, 0);
}