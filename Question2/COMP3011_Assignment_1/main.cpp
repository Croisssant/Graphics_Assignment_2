#include <iostream>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "loadimage.h"

using namespace std;



int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Question 2", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

   
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLuint tex;
    tex = loadimage("Sprite_Dice.bmp");

    struct UV
    {
        float ux, uy, vx, vy;
    };

    // U == Upper Right Corner
    // V == Lower Left Corner

    // UV Mapping for Number 1 Dice Face
    UV sprite_uvs_1[16] =
    {
        /*U                  V*/
        {0.166667, 1.000000, 0.000000, 0.833333},
        {0.166667, 0.833333, 0.000000, 0.666667},
        {0.166667, 0.666667, 0.000000, 0.500000},
        {0.166667, 0.500000, 0.000000, 0.333333},
        {0.166667, 0.333333, 0.000000, 0.166667},
        {0.166667, 0.166667, 0.000000, 0.000000},

    };

    UV sprite_uvs_2[16] =
    {
        /*U                  V*/
        {0.333333, 1.000000, 0.166667, 0.833333},
        {0.333333, 0.833333, 0.166667, 0.666667},
        {0.333333, 0.666667, 0.166667, 0.500000},
        {0.333333, 0.500000, 0.166667, 0.333333},
        {0.333333, 0.333333, 0.166667, 0.166667},
        {0.333333, 0.166667, 0.166667, 0.000000},

    };

    UV sprite_uvs_3[16] =
    {
        /*U                  V*/
        {0.500000, 1.000000, 0.333333, 0.833333},
        {0.500000, 0.833333, 0.333333, 0.666667},
        {0.500000, 0.666667, 0.333333, 0.500000},
        {0.500000, 0.500000, 0.333333, 0.333333},
        {0.500000, 0.333333, 0.333333, 0.166667},
        {0.500000, 0.166667, 0.333333, 0.000000},

    };

    UV sprite_uvs_4[16] =
    {
        /*U                  V*/
        {0.666667, 1.000000, 0.500000, 0.833333},
        {0.666667, 0.833333, 0.500000, 0.666667},
        {0.666667, 0.666667, 0.500000, 0.500000},
        {0.666667, 0.500000, 0.500000, 0.333333},
        {0.666667, 0.333333, 0.500000, 0.166667},
        {0.666667, 0.166667, 0.500000, 0.000000},

    };

    UV sprite_uvs_5[16] =
    {
        /*U                  V*/
        {0.833333, 1.000000, 0.666667, 0.833333},
        {0.833333, 0.833333, 0.666667, 0.666667},
        {0.833333, 0.666667, 0.666667, 0.500000},
        {0.833333, 0.500000, 0.666667, 0.333333},
        {0.833333, 0.333333, 0.666667, 0.166667},
        {0.833333, 0.166667, 0.666667, 0.000000},

    };

    UV sprite_uvs_6[16] =
    {
        /*U                  V*/
        {1.000000, 1.000000, 0.833333, 0.833333},
        {1.000000, 0.833333, 0.833333, 0.666667},
        {1.000000, 0.666667, 0.833333, 0.500000},
        {1.000000, 0.500000, 0.833333, 0.333333},
        {1.000000, 0.333333, 0.833333, 0.166667},
        {1.000000, 0.166667, 0.833333, 0.000000},

    };
    const int num_uvs = 6;
    int frame = 0;
    int anim_frame = 0;
    const int anim_speed = 2500;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {      
     
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glBindTexture(GL_TEXTURE_2D, tex);
        
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        
        frame++;
        if (frame % anim_speed == 0)
        {
            anim_frame = (anim_frame + 1) % num_uvs;
        }
        
        UV uv1 = sprite_uvs_1[anim_frame];
        UV uv2 = sprite_uvs_2[anim_frame];
        UV uv3 = sprite_uvs_3[anim_frame];
        UV uv4 = sprite_uvs_4[anim_frame];
        UV uv5 = sprite_uvs_5[anim_frame];
        UV uv6 = sprite_uvs_6[anim_frame];
        

       // glRotatef(0.01f, 1.f, 1.f, 1.f);
        glRotatef(0.01f, 1.f, 1.f, 1.f);
        float r = 0.5f;

        glBegin(GL_TRIANGLES);

        // Back Face
        glTexCoord2f(uv6.vx, uv6.vy);
        glVertex3f(-r, -r, r);    
        glTexCoord2f(uv6.vx, uv6.uy);
        glVertex3f(-r, r, r);
        glTexCoord2f(uv6.ux, uv6.uy);
        glVertex3f(r, r, r);

        glTexCoord2f(uv6.ux, uv6.uy);
        glVertex3f(r, r, r);
        glTexCoord2f(uv6.ux, uv6.vy);
        glVertex3f(r, -r, r);
        glTexCoord2f(uv6.vx, uv6.vy);
        glVertex3f(-r, -r, r);
        

        // Near Face
        glTexCoord2f(uv1.vx, uv1.vy);
        glVertex3f(r, r, -r);
        glTexCoord2f(uv1.vx, uv1.uy);
        glVertex3f(-r, r, -r);
        glTexCoord2f(uv1.ux, uv1.uy);
        glVertex3f(-r, -r, -r);

        glTexCoord2f(uv1.ux, uv1.uy);
        glVertex3f(-r, -r, -r);
        glTexCoord2f(uv1.ux, uv1.vy);
        glVertex3f(r, -r, -r);
        glTexCoord2f(uv1.vx, uv1.vy);
        glVertex3f(r, r, -r);

        

        // Right Face
        glTexCoord2f(uv3.ux, uv3.uy);
        glVertex3f(r, r, -r);
        glTexCoord2f(uv3.ux, uv3.vy);
        glVertex3f(r, -r, -r);
        glTexCoord2f(uv3.vx, uv3.vy);
        glVertex3f(r, -r, r);

        glTexCoord2f(uv3.vx, uv3.vy);
        glVertex3f(r, -r, r);
        glTexCoord2f(uv3.vx, uv3.uy);
        glVertex3f(r, r, r);
        glTexCoord2f(uv3.ux, uv3.uy);
        glVertex3f(r, r, -r);

        

        //Left Face
        glTexCoord2f(uv4.ux, uv4.uy);
        glVertex3f(-r, -r, r);
        glTexCoord2f(uv4.ux, uv4.vy);
        glVertex3f(-r, -r, -r);
        glTexCoord2f(uv4.vx, uv4.vy);
        glVertex3f(-r, r, -r);
        

        glTexCoord2f(uv4.vx, uv4.vy);
        glVertex3f(-r, r, -r);
        glTexCoord2f(uv4.vx, uv4.uy);
        glVertex3f(-r, r, r);
        glTexCoord2f(uv4.ux, uv4.uy);
        glVertex3f(-r, -r, r);
        

        
        //Bottom Face
        glTexCoord2f(uv2.ux, uv2.uy);
        glVertex3f(r, r, -r);
        glTexCoord2f(uv2.ux, uv2.vy);
        glVertex3f(r, r, r);
        glTexCoord2f(uv2.vx, uv2.vy);
        glVertex3f(-r, r, r);

        glTexCoord2f(uv2.vx, uv2.vy);
        glVertex3f(-r, r, r);
        glTexCoord2f(uv2.vx, uv2.uy);
        glVertex3f(-r, r, -r);
        glTexCoord2f(uv2.ux, uv2.uy);
        glVertex3f(r, r, -r);

        

        //Top Face
        glTexCoord2f(uv5.ux, uv5.uy);
        glVertex3f(-r, -r, r);
        glTexCoord2f(uv5.ux, uv5.vy);
        glVertex3f(r, -r, r);
        glTexCoord2f(uv5.vx, uv5.vy);
        glVertex3f(r, -r, -r);

        glTexCoord2f(uv5.vx, uv5.vy);
        glVertex3f(r, -r, -r);
        glTexCoord2f(uv5.vx, uv5.uy);
        glVertex3f(-r, -r, -r);
        glTexCoord2f(uv5.ux, uv5.uy);
        glVertex3f(-r, -r, r);
            

        glEnd();

        glDisable(GL_TEXTURE_2D);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
