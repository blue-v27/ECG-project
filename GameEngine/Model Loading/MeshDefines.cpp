#include "MeshDefines.h"
#include "texture.h"
#include "TextureDefine.h"
#include "..\Game\DataSturctures\fArray.h"

void MeshDefines::Start()
{
	GLuint m_tex = 0;

	m_meshes.push_back(m_loader.loadObj(MeshDefines::cube));
	m_meshes.push_back(m_loader.loadObj(MeshDefines::sphere));
	m_meshes.push_back(m_loader.loadObj(MeshDefines::plane));

	m_tex = loadBMP(TextureDefine::Wood);
	Array<Texture> woodArray;
	woodArray.PushLast(Texture());
	woodArray[0].id = m_tex;
	woodArray[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::cube, woodArray));

	m_tex = loadBMP(TextureDefine::Water);	
	Array<Texture> Water;
	Water.PushLast(Texture());
	Water[0].id = m_tex;
	Water[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::water, Water));

	m_tex = loadBMP(TextureDefine::Dirt);
	Array<Texture> dirt;
	dirt.PushLast(Texture());
	dirt[0].id = m_tex;
	dirt[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::plane, dirt));

	m_meshes.push_back(m_loader.loadObj(MeshDefines::knife));
	m_meshes.push_back(m_loader.loadObj(MeshDefines::pistol));

	m_tex = loadBMP(TextureDefine::Grass);
	Array<Texture> grass;
	grass.PushLast(Texture());
	grass[0].id = m_tex;
	grass[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::grass, grass));

	m_tex = loadBMP(TextureDefine::Rock);
	Array<Texture> rock;
	rock.PushLast(Texture());
	rock[0].id = m_tex;
	rock[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::rock, rock));

	m_tex = loadBMP(TextureDefine::treeStem);
	Array<Texture> treeStem;
	treeStem.PushLast(Texture());
	treeStem[0].id = m_tex;
	treeStem[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::treeStem, treeStem));

	m_meshes.push_back(m_loader.loadObj(MeshDefines::treeLeaves, grass));

	m_tex = loadBMP(TextureDefine::Rock);
	m_meshes.push_back(m_loader.loadObj(MeshDefines::sphere, rock));

	m_tex = loadBMP(TextureDefine::Dirt);
	m_meshes.push_back(m_loader.loadObj(MeshDefines::cliff, dirt));

	m_meshes.push_back(m_loader.loadObj(MeshDefines::clock, rock));

	m_tex = loadBMP(TextureDefine::black);
	Array<Texture> black;
	black.PushLast(Texture());
	black[0].id = m_tex;
	black[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::build1, black));

	m_meshes.push_back(m_loader.loadObj(MeshDefines::build2, black));

	m_meshes.push_back(m_loader.loadObj(MeshDefines::build3, black));

	m_tex = loadBMP(TextureDefine::black);
	m_meshes.push_back(m_loader.loadObj(MeshDefines::plane, black));

	m_tex = loadBMP(TextureDefine::Orange);
	Array<Texture> orange;
	orange.PushLast(Texture());
	orange[0].id = m_tex;
	orange[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::sphere, orange));

}	


int MeshDefines::GetMeshIndex(Mesh mesh)
{
	int nrOfMesh = m_meshes.size();

	for (int i = 0; i < nrOfMesh; ++i)
	{
		if (mesh.vbo == m_meshes.at(i).vbo)
			return i;
	}

	return 0;
}
