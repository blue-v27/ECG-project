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
	static constexpr char* cliff		= "Resources/Models/ForestRoad.obj";
	static constexpr char* clock		= "Resources/Models/clock.obj";
	static constexpr char* build1		= "Resources/Models/ResidentialBuildings003.obj";
	static constexpr char* build2		= "Resources/Models/ResidentialBuildings007.obj";
	static constexpr char* build3		= "Resources/Models/ResidentialBuildings010.obj";

	void Start();
	Mesh GetMesh(int index) { return m_meshes.at(index); }

	int GetMeshIndex(Mesh mesh);

	int GetMeshCount() { return m_meshes.size(); }

	void IsActive(bool val) { m_isActive = val; }
	bool IsActive()			{ return m_isActive; }

#define MESH_DEFINES MeshDefines::Instance()

#define MESH_CUBE    0
#define MESH_SPHERE  1
#define MESH_PLANE   2
#define MESH_BOX	 3
#define MESH_WATER   4
#define MESH_GROUND  5
#define MESH_KNIFE   6
#define MESH_PISTOL  7
#define MESH_GRASS   8
#define MESH_ROCK	 9
#define MESH_TREE	 10
#define MESH_FULLTRE 11
#define MESH_SUN	 12
#define MESH_CLIFF   13
#define MESH_CLOCK   14
#define MESH_BUILD1  15
#define MESH_BUILD2  16
#define MESH_BUILD3  17
#define MESH_GROUNDF 18
#define MESH_FIRE	 19
};