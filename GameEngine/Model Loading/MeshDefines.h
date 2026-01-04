#pragma once

#include "meshLoaderObj.h"

class MeshDefines
{
private:
	MeshDefines() = default;
	~MeshDefines() = default;

	MeshLoaderObj m_loader;
	std::vector<Mesh> m_meshes;

	bool m_isActive = false;
public:
	static constexpr char* sphere = "Resources/Models/sphere.obj";
	static constexpr char* cube   = "Resources/Models/cube.obj";
	static constexpr char* water  = "Resources/Models/plane1.obj";
	static constexpr char* plane  = "Resources/Models/plane.obj";
	static constexpr char* knife  = "Resources/Models/m9bayo2.obj";
	static constexpr char* pistol = "Resources/Models/M9.obj";

	static MeshDefines& Instance()
	{
		static MeshDefines instance;
		return instance;
	}

	MeshDefines(const MeshDefines&) = delete;
	MeshDefines& operator=(const MeshDefines&) = delete;
	MeshDefines(MeshDefines&&) = delete;
	MeshDefines& operator=(MeshDefines&&) = delete;

	void Start();
	Mesh GetMesh(int index) { return m_meshes.at(index); }

	int GetMeshIndex(Mesh mesh);

	int GetMeshCount() { return m_meshes.size(); }

	void IsActive(bool val) { m_isActive = val; }
	bool IsActive()			{ return m_isActive; }

#define MESH_DEFINES MeshDefines::Instance()

#define CUBE    0
#define SPHERE  1
#define PLANE   2
#define BOX	    3
#define WATER   4
#define GROUND  5
#define KNIFE   6
#define PISTOL  7
};