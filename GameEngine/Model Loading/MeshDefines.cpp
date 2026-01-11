#include "MeshDefines.h"
#include "texture.h"
#include "TextureDefine.h"

void MeshDefines::Start()
{
	GLuint m_tex = 0;
	std::vector<Texture> m_textures;

	m_meshes.push_back(m_loader.loadObj(MeshDefines::cube));
	m_meshes.push_back(m_loader.loadObj(MeshDefines::sphere));
	m_meshes.push_back(m_loader.loadObj(MeshDefines::plane));

	m_tex = loadBMP(TextureDefine::Wood);
	m_textures.push_back(Texture());
	m_textures[0].id = m_tex;
	m_textures[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::cube, m_textures));
	m_textures.clear();

	m_tex = loadBMP(TextureDefine::Water);
	m_textures.push_back(Texture());
	m_textures[0].id = m_tex;
	m_textures[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::water, m_textures));
	m_textures.clear();

	m_tex = loadBMP(TextureDefine::Dirt);
	m_textures.push_back(Texture());
	m_textures[0].id = m_tex;
	m_textures[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::plane, m_textures));
	m_textures.clear();

	m_meshes.push_back(m_loader.loadObj(MeshDefines::knife));
	m_meshes.push_back(m_loader.loadObj(MeshDefines::pistol));

	m_tex = loadBMP(TextureDefine::Grass);
	m_textures.push_back(Texture());
	m_textures[0].id = m_tex;
	m_textures[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::grass, m_textures));
	m_textures.clear();

	m_tex = loadBMP(TextureDefine::Rock);
	m_textures.push_back(Texture());
	m_textures[0].id = m_tex;
	m_textures[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::rock, m_textures));
	m_textures.clear();

	m_tex = loadBMP(TextureDefine::treeStem);
	m_textures.push_back(Texture());
	m_textures[0].id = m_tex;
	m_textures[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::treeStem, m_textures));
	m_textures.clear();

	m_tex = loadBMP(TextureDefine::Grass);
	m_textures.push_back(Texture());
	m_textures[0].id = m_tex;
	m_textures[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::treeLeaves, m_textures));
	m_textures.clear();

	m_tex = loadBMP(TextureDefine::Rock);
	m_textures.push_back(Texture());
	m_textures[0].id = m_tex;
	m_textures[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::sphere, m_textures));
	m_textures.clear();

#if 0
	m_tex = loadBMP(TextureDefine::Dirt);
	m_textures.push_back(Texture());
	m_textures[0].id = m_tex;
	m_textures[0].type = "texture_diffuse";
	m_meshes.push_back(m_loader.loadObj(MeshDefines::cliff, m_textures));
	m_textures.clear();
#endif
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
