#pragma once

#include "meshLoaderObj.h"
#include "../Game/fSingleton.h"

class MeshDefines : public fSingleton<MeshDefines>
{
private:

	MeshLoaderObj m_loader;
	std::vector<Mesh> m_meshes;

	bool m_isActive = false;
public:
	static constexpr char* sphere		= "Resources/Models/sphere.obj";
	static constexpr char* cube			= "Resources/Models/cube.obj";
	static constexpr char* water		= "Resources/Models/plane1.obj";
	static constexpr char* plane		= "Resources/Models/plane.obj";
	static constexpr char* knife		= "Resources/Models/m9bayo2.obj";
	static constexpr char* pistol		= "Resources/Models/M9.obj";
	static constexpr char* grass		= "Resources/Models/Grass.obj";
	static constexpr char* rock			= "Resources/Models/Rock1.obj";
	static constexpr char* treeStem     = "Resources/Models/MapleTreeStem.obj";
	static constexpr char* treeLeaves   = "Resources/Models/MapleTreeLeaves.obj";

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
#define GRASS   8
#define ROCK	9
#define TREE	10
#define FULLTRE 11
#define SUN		12
#define SKY		13
};