
//! \file tuto9_texture1.cpp utilisation d'un shader 'utilisateur' pour afficher un objet Mesh avec une texture.

#include "mat.h"
#include "mesh.h"
#include "wavefront.h"
#include "texture.h"

#include "orbiter.h"
#include "program.h"
#include "uniforms.h"
#include "draw.h"

#include "app.h"        // classe Application a deriver


class TP : public App
{
public:
    // constructeur : donner les dimensions de l'image, et eventuellement la version d'openGL.
    TP( ) : App(1024, 640) {}

    int init( )
    {
        m_objet= read_mesh("data/cube.obj");
        gl.light( Point(300, 2000, 300 ),White() );
        gl.lighting(false);
        Point pmin, pmax;
        m_objet.bounds(pmin, pmax);
        m_camera.lookat(pmin, pmax);

        m_texture= read_texture(0, "data/debug2x2red.png");

        // etape 1 : creer le shader program
        m_program= read_program("tutos/tuto9_texture1.glsl");
        program_print_errors(m_program);

        // etat openGL par defaut
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);        // couleur par defaut de la fenetre

        glClearDepth(1.f);                          // profondeur par defaut
        glDepthFunc(GL_LESS);                       // ztest, conserver l'intersection la plus proche de la camera
        glEnable(GL_DEPTH_TEST);                    // activer le ztest

        return 0;   // ras, pas d'erreur
    }

    // destruction des objets de l'application
    int quit( )
    {
        // etape 3 : detruire le shader program
        release_program(m_program);

        m_objet.release();
        glDeleteTextures(1, &m_texture);
        return 0;
    }

    // dessiner une nouvelle image
    int render( )
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // deplace la camera
        int mx, my;
        unsigned int mb= SDL_GetRelativeMouseState(&mx, &my);
        if(mb & SDL_BUTTON(1))              // le bouton gauche est enfonce
            m_camera.rotation(mx, my);
        else if(mb & SDL_BUTTON(3))         // le bouton droit est enfonce
            m_camera.move(mx);
        else if(mb & SDL_BUTTON(2))         // le bouton du milieu est enfonce
            m_camera.translation((float) mx / (float) window_width(), (float) my / (float) window_height());

        // etape 2 : dessiner m_objet avec le shader program
        // configurer le pipeline
        glUseProgram(m_program);
        Point pos1 = RotationY(global_time()/20)(Point(100, 200,50 ));
        vec3 pos(pos1);
        // configurer le shader program
        // . recuperer les transformations
        Transform model= Scale(1,1,1);
        Transform view= m_camera.view();
        Transform projection= m_camera.projection(window_width(), window_height(), 45);

        // . composer les transformations : model, view et projection
        Transform mvp= projection * view * model;
        vec3 lightColor(1,1,1);
        // . parametrer le shader program :
        //   . transformation : la matrice declaree dans le vertex shader s'appelle mvpMatrix
        program_uniform(m_program, "mvpMatrix", mvp);
        program_uniform(m_program, "objectColor", vec3(1.0f, 0.5f, 0.31f));
        program_uniform(m_program, "lightColor", lightColor);
        program_uniform(m_program, "lightPos", pos);

        program_uniform(m_program, "model", model);

        // . parametres "supplementaires" :
        //   . utilisation d'une texture configuree sur l'unite 0, le fragment shader declare "uniform sampler2D texture0;"


        // go !
        draw(m_objet, m_program);
        return 1;
    }

protected:
    Mesh m_objet;
    Orbiter m_camera;
    GLuint m_texture;
    GLuint m_program;

    DrawParam gl ;
};


int main( int argc, char **argv )
{
    TP tp;
    tp.run();

    return 0;
}