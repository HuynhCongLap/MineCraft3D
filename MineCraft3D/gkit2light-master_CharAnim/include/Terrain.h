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
#include "window.h"
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

        void getLight(vec3 light_pos)
        {
          light_position = light_pos;
        }

        void getLight1(vec3 light_pos)
        {
          light1_position = light_pos;
        }
        void getView(vec3 view_pos)
        {
          view_position = view_pos;
        }

    private:
        unsigned int texture;
        GLuint texcoord_buffer;
        GLuint normal_buffer;
        Mesh m_terrain;
        GLuint m_program;
        unsigned int instanceVBO, VBO, colorVBO;
        unsigned int VAO;

        GLuint ice_texture;
        GLuint water_texture;
        GLuint land_texture;
        GLuint mou_texture;
        GLuint top_texture;
        GLuint grass_side_texture;
        GLuint top_grass;
        GLuint sampler;

        vec3 light_position = vec3(0,0,0);
        vec3 light1_position = vec3(0,0,0);
        vec3 view_position = vec3(0,0,0);

};

#endif // TERRAIN_H
