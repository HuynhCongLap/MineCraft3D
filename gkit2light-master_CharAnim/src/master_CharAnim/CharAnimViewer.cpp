
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "CharAnimViewer.h"

using namespace std;



CharAnimViewer* CharAnimViewer::psingleton = NULL;


CharAnimViewer::CharAnimViewer() : Viewer()
{
	psingleton = this;
}


int CharAnimViewer::init()
{
    Viewer::init();
    cout<<"==>master_CharAnim/CharAnimViewer"<<endl;
    m_camera.lookat( Point(0,100,10), 800 );
    gl.light( Point(300, 300, 300 ), White());

    terrain.create_terrain("data/terrain/Clipboard01.png");
    terrain.init_terrain();

//    for(int i=0; i<10; i++){
//
//        translation[i] = vec3(0,i,0) ;
//
//    }
//    m_objet= read_mesh("data/cube.obj");
//
//   //m_objet= read_mesh("data/knight.obj");
//     // etape 1 : creer le shader program
//   // m_program= read_program("tutos/tuto9_texture1.glsl");
//    m_program= read_program("tutos/tuto10.glsl");
//    program_print_errors(m_program);
//
//    glGenBuffers(1, &instanceVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * 10, &translation[0], GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferData(GL_ARRAY_BUFFER, m_objet.vertex_buffer_size(), m_objet.vertex_buffer(), GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//        glEnableVertexAttribArray(1);
//        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glVertexAttribDivisor(1, 1); // tell OpenGL this is an instanced vertex attribute.


    return 0;
}





int CharAnimViewer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw_quad( RotationX(-90)*Scale(500,500,1) );

    Viewer::manageCameraLight();
    gl.camera(m_camera);


        // configurer le shader program
        // . recuperer les transformations
    Transform model= Scale(1,1,1);
    Transform view= m_camera.view();
    Transform projection= m_camera.projection(window_width(), window_height(), 45);

        // . composer les transformations : model, view et projection
    Transform mv= view * model;
    Transform mvp= projection * mv;

    terrain.draw_terrain(mvp);

//        vec3 pos(Point(300, 300, 300 ));
//        // configurer le shader program
//        // . recuperer les transformations
//        Transform model= Scale(50,50,50)*RotationY(global_time()/20);
//        Transform view= m_camera.view();
//        Transform projection= m_camera.projection(window_width(), window_height(), 45);
//
//        // . composer les transformations : model, view et projection
//        Transform mvp= projection * view * model;
//        vec3 lightColor(1,1,1);
//        // . parametrer le shader program :
//        //   . transformation : la matrice declaree dans le vertex shader s'appelle mvpMatrix
//        program_uniform(m_program, "mvpMatrix", mvp);
//        program_uniform(m_program, "objectColor", vec3(0.f, 0.f, 0.f));
//        program_uniform(m_program, "lightColor", lightColor);
//
//        program_uniform(m_program, "materialAmbient", vec3(0.19225f, 0.19225f, 0.19225f));
//        program_uniform(m_program, "materialDiffuse", vec3(0.50754f, 0.50754f, 0.50754f));
//        program_uniform(m_program, "materialSpecular", vec3(0.508273f, 0.508273f, 0.508273f));
//        program_uniform(m_program, "materialShininess", 100.2f);
//
//
//        program_uniform(m_program, "lightPos", pos);
//        program_uniform(m_program, "viewPos", vec3(m_camera.position()));
//
//        program_uniform(m_program, "model", model);
//
//
//
//        // go !
//        draw(m_objet, m_program);


    return 1;
}


int CharAnimViewer::update( const float time, const float delta )
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.

	if (key_state('n')) {  }
	if (key_state('b')) {  }


    return 0;
}



