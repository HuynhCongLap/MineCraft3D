#ifndef TERRAIN_H
#define TERRAIN_H
#include "image.h"
#include <vector>
#include "mat.h"
#include "mesh.h"
#include "image_io.h"
#include "program.h"
#include "wavefront.h"
#include "orbiter.h"
#include "uniforms.h"
#include "texture.h"

class Terrain
{
    public:
        Terrain();
        void create_terrain(const char* filename);
        void init_terrain();
        void draw_terrain(Transform& mvp);
        std::vector<vec3> positions;
        std::vector<vec3> colors;
        virtual ~Terrain();
        int height = 15;
        float realHeight=0;

    protected:

    private:
        unsigned int texture;
        GLuint texcoord_buffer;
        Mesh m_terrain;
        GLuint m_program;
        unsigned int instanceVBO, VBO, colorVBO;
        unsigned int VAO;

        GLuint ice_texture;
        GLuint water_texture;
        GLuint land_texture;
        GLuint mou_texture;
        GLuint top_texture;
        GLuint sampler;

};

#endif // TERRAIN_H
