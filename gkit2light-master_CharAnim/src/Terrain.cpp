#include "Terrain.h"

Terrain::Terrain()
{
    //ctor
}

Terrain::~Terrain()
{
    //dtor
    release_program(m_program);
    m_terrain.release();
}

void Terrain::init_terrain()
{

    m_program = read_program("tutos/tuto5GL.glsl");
    program_print_errors(m_program);

    m_terrain= read_mesh("data/cube.obj");

     glGenBuffers(1, &instanceVBO);
     glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positions.size(), &positions[0], GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glGenBuffers(1, &colorVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positions.size(), &colors[0], GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);


//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glBindVertexArray(VAO);
//
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, m_terrain.vertex_buffer_size(),m_terrain.vertex_buffer(), GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//
//    glGenBuffers(1, &texcoord_buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer);
//    glBufferData(GL_ARRAY_BUFFER, m_terrain.texcoord_buffer_size(), m_terrain.texcoord_buffer(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//


//    glEnableVertexAttribArray(3);
//    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glVertexAttribDivisor(3, 1);
//
//
//    glEnableVertexAttribArray(4);
//    glBindBuffer(GL_ARRAY_BUFFER, colorVBO); // this attribute comes from a different vertex buffer
//    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glVertexAttribDivisor(4, 1);


    // texture


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_terrain.vertex_buffer_size(), m_terrain.vertex_buffer(), GL_STATIC_DRAW);

    GLint position= glGetAttribLocation(m_program, "position");


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

        // texcoord buffer
    glGenBuffers(1, &texcoord_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_terrain.texcoord_buffer_size(), m_terrain.texcoord_buffer(), GL_STATIC_DRAW);

       // configurer l'attribut texcoord, cf declaration dans le vertex shader : in vec2 texcoord;
    GLint texcoord= glGetAttribLocation(m_program, "texcoord");

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

     ;
     glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
     glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glVertexAttribDivisor(3, 1);
     glEnableVertexAttribArray(3);

       // nettoyage
    m_terrain.release();
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

        // etape 3 : texture
    ImageData image= read_image_data("data/debug2x2red.png");

//////////////////////////////////
    glGenSamplers(1, &sampler);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    ice_texture= read_texture(0, "data/blocks/wool_colored_blue.png");
    water_texture= read_texture(0, "data/blocks/snow.png");
    land_texture= read_texture(0, "data/blocks/wool_colored_lime.png");
    mou_texture= read_texture(0, "data/blocks/concrete_green.png");
    top_texture= read_texture(0, "data/blocks/concrete_brown.png");
//////////////////////////////////

     // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
//
//        glTexImage2D(GL_TEXTURE_2D, 0,
//           GL_RGBA, image.width, image.height, 0,
//           GL_RGB, GL_UNSIGNED_BYTE, image.buffer());
//
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

       // nettoyage
       glBindTexture(GL_TEXTURE_2D, 0);
       glUseProgram(0);

}
void Terrain::draw_terrain(Transform& mvp)
{

    glUseProgram(m_program);
        // . composer les transformations : model, view et projectio

    program_uniform(m_program, "mvpMatrix", mvp);

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, m_objet.vertex_count());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ice_texture);
    glBindSampler(0, sampler);

    glActiveTexture(GL_TEXTURE0 +1);
    glBindTexture(GL_TEXTURE_2D, water_texture);
    glBindSampler(1, sampler);

    glActiveTexture(GL_TEXTURE0 +2);
    glBindTexture(GL_TEXTURE_2D,  land_texture);
    glBindSampler(2, sampler);

    glActiveTexture(GL_TEXTURE0 +3);
    glBindTexture(GL_TEXTURE_2D, mou_texture);
    glBindSampler(3, sampler);

    glActiveTexture(GL_TEXTURE0 +4);
    glBindTexture(GL_TEXTURE_2D, top_texture);
    glBindSampler(4, sampler);

       // uniform sampler2D declares par le fragment shader
    GLint location;
    location= glGetUniformLocation(m_program, "ice_texture");
    glUniform1i(location, 0);

    location= glGetUniformLocation(m_program, "water_texture");
    glUniform1i(location, 1);

     location= glGetUniformLocation(m_program, "land_texture");
    glUniform1i(location, 2);

     location= glGetUniformLocation(m_program, "mou_texture");
    glUniform1i(location, 3);

     location= glGetUniformLocation(m_program, "top_texture");
    glUniform1i(location, 4);


    glDrawArraysInstanced(GL_TRIANGLES, 0, m_terrain.vertex_count(), positions.size()); // 100 triangles of 6 vertices each
    //glDrawArrays(GL_TRIANGLES, 0, m_terrain.vertex_count());
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
    glBindVertexArray(0);


}


void Terrain::create_terrain(const char* filename)
{

    Image data= read_image(filename);
    float scale= 20;


    for(int y= 0; y +1 < data.height(); y++)
    for(int x= 0; x +1 < data.width(); x++)
    {
        // recupere l'altitude de 4 points voisins, dans le sens trigo
        float a= data(x, y).r * scale;
        float b= data(x +1, y).r * scale;
        float c= data(x +1, y +1).r * scale;
        float d= data(x, y +1).r * scale;

        float h = (a+b+c+d)/4;
        if (h>realHeight)
            realHeight = h;

    }

    for(int y= 0; y +1 < data.height(); y++)
    for(int x= 0; x +1 < data.width(); x++)
    {
        // recupere l'altitude de 4 points voisins, dans le sens trigo
        float a= data(x, y).r * scale;
        float b= data(x +1, y).r * scale;
        float c= data(x +1, y +1).r * scale;
        float d= data(x, y +1).r * scale;

        float realh = (a+b+c+d)/4;
        int h = (height*realh)/realHeight;
        positions.push_back(vec3(x,h,y));
        colors.push_back(vec3(realh/realHeight ,realh/realHeight ,realh/realHeight ));
    }
}
