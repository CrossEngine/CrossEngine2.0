/**************************************************************
 * Program Title: CrossEngine
 * Filename: RenderObject.cpp
 * Author: Blake Rogan
 * Last modified: 4/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Render/RenderObject.hpp>
#include <cassert>


CrossEngine::Render::Model::Model(const CrossEngine::Render::MeshCompileVector &meshes) {

}

CrossEngine::Render::Model::~Model() {

}

void CrossEngine::Render::Mesh::AddVertex(float x, float y, float z) {
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}

void CrossEngine::Render::Mesh::AddIndex(unsigned int index) {
    indices.push_back(index);
}

void CrossEngine::Render::Mesh::AddPoint(unsigned int point) {
    assert(meshType == CrossEngine::Render::Mesh_Points);
    AddIndex(point);
}

void CrossEngine::Render::Mesh::AddLine(unsigned int from, unsigned int to) {
    assert(meshType == CrossEngine::Render::Mesh_Lines);
    AddIndex(from);
    AddIndex(to);
}

void CrossEngine::Render::Mesh::AddTriangle(unsigned int v1, unsigned int v2, unsigned int v3) {
    assert(meshType == CrossEngine::Render::Mesh_Triangles || meshType == CrossEngine::Render::Mesh_Triangle_Strip);
    AddIndex(v1);
    AddIndex(v2);
    AddIndex(v3);
}

void CrossEngine::Render::Mesh::AddTriangleQuat(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4) {
    assert(meshType == CrossEngine::Render::Mesh_Triangles || meshType == CrossEngine::Render::Mesh_Triangle_Strip);
    AddIndex(v1);
    AddIndex(v2);
    AddIndex(v3);

    AddIndex(v2);
    AddIndex(v3);
    AddIndex(v4);
}

void CrossEngine::Render::Mesh::AddQuad(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4) {
    assert(meshType == CrossEngine::Render::Mesh_Quads);
    AddIndex(v1);
    AddIndex(v2);
    AddIndex(v3);
    AddIndex(v4);
}

CrossEngine::Render::RenderObject::RenderObject() {

}

CrossEngine::Render::RenderObject::~RenderObject() {

}

void CrossEngine::Render::RenderObject::AddMesh(CrossEngine::Render::Mesh *mesh) {
    meshes.push_back(mesh);
}

CrossEngine::Render::MeshVector CrossEngine::Render::RenderObject::GetMeshes() {
    return meshes;
}

CrossEngine::Render::MeshCompileVector CrossEngine::Render::RenderObject::Compile(const CrossEngine::Render::MeshCompilerFunction &compiler) {
    MeshCompileVector compiled;
    for (const auto &mesh : meshes) {
        compiled.push_back(compiler(mesh));
    }
    return compiled;
}
