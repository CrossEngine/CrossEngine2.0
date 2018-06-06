/**************************************************************
 * Program Title: CrossEngine
 * Filename: RenderObject.hpp
 * Author: Blake Rogan
 * Last modified: 4/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_RENDEROBJECT_HPP
#define CROSSENGINE_RENDEROBJECT_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>

namespace CrossEngine {
    namespace Render {

        /**
         *
         */
        typedef void* CompiledMesh;
        /**
         *
         */
        typedef Util::Containers::Vector<CompiledMesh> MeshCompileVector;

        /**
         *
         */
        class Model {
        private:

        public:
            CrossEngineAPI explicit Model(const MeshCompileVector& meshes);

            CrossEngineAPI ~Model();

            CrossEngineAPI virtual void Render() = 0;
        };

        /**
         *
         */
        enum MeshType {
            Mesh_Triangles,
            Mesh_Triangle_Strip,
            Mesh_Quads,
            Mesh_Lines,
            Mesh_Points,
        };

        /**
         *
         */
        struct Mesh {
            MeshType meshType; /** */
            Util::Containers::Vector<float> vertices;
            Util::Containers::Vector<unsigned int> indices;

            CrossEngineAPI void AddVertex(float x, float y, float z);

            CrossEngineAPI void AddIndex(unsigned int index);

            CrossEngineAPI void AddPoint(unsigned int point);

            CrossEngineAPI void AddLine(unsigned int from, unsigned int to);

            CrossEngineAPI void AddTriangle(unsigned int v1, unsigned int v2, unsigned int v3);

            CrossEngineAPI void AddTriangleQuat(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);

            CrossEngineAPI void AddQuad(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);
        };

        /**
         *
         */
        typedef Util::Containers::Vector<Mesh*> MeshVector;
        /**
         *
         */
        typedef std::function<CompiledMesh(Mesh*)> MeshCompilerFunction;

        /**
         *
         */
        class RenderObject {
        private:
            MeshVector meshes; /** */
        public:
            /**
             *
             */
            CrossEngineAPI RenderObject();

            /**
             *
             */
            CrossEngineAPI ~RenderObject();

            /**
             *
             * \param mesh
             */
            CrossEngineAPI void AddMesh(Mesh* mesh);

            /**
             *
             * \return
             */
            CrossEngineAPI MeshVector GetMeshes();

            /**
             *
             * \param compiler
             * \return
             */
            CrossEngineAPI virtual MeshCompileVector Compile(const MeshCompilerFunction& compiler);
        };
    }
}


#endif //CROSSENGINE_RENDEROBJECT_HPP
