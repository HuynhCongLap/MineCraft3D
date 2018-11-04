
#ifndef _CHARANIMVIEWER_H
#define _CHARANIMVIEWER_H


#include "quaternion.h"
#include "Viewer.h"
#include "uniforms.h"
#include "wavefront.h"
#include "Terrain.h"
class CharAnimViewer : public Viewer
{
public:
    CharAnimViewer();

    int init();
    int render();
    int update( const float time, const float delta );

	static CharAnimViewer& singleton() { return *psingleton;  }

private:
	static CharAnimViewer* psingleton;
	int quit() {

        release_program(m_program);
        m_objet.release();
        return 1;
    }
protected:

    Mesh m_objet;
    GLuint m_texture;


    Terrain terrain ;
    Mesh m_grid;

    GLuint m_program;
    vec3 translation[10];
    unsigned int instanceVBO;
    unsigned int VBO, VAO, VBO1;

    GLuint base_texture;
    GLuint detail_texture;
    GLuint sampler;

};



#endif
