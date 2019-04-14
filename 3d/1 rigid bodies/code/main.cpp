/*
    Bullet Continuous Collision Detection and Physics Library
    Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it freely,
    subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
       If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    This is the official 'Hello, World' example cleaned up for additional simplicity and clarity.
*/

#include <memory>
#include <vector>
#include <iostream>

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>
#include <Scene.hpp>
#include <Physics_World.hpp>
#include <Rigid_Body.hpp>
#include <Static_Rigid_Body.hpp>
#include <Dynamic_Rigid_Body.hpp>
#include <Box_Shape.hpp>
#include<Shpere_Shape.hpp>
#include <Tank.hpp>

using namespace std;
using namespace glt;



int main ()
{
    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                       PHYSISCS WORLD INITIALIZATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */


	shared_ptr<Physics_World> dynamicsWorld(new Physics_World);



    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                                SIMULATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    // Se crea la ventana y el contexto de OpenGL asociado a ella:

    sf::Window window
    (
        sf::VideoMode(1024, 720),
        "Bullet Rigid Bodies",
        sf::Style::Default,
        sf::ContextSettings(24, 0, 0, 3, 2, sf::ContextSettings::Core)      // Se usa OpenGL 3.2 core profile
    );

    // Se determinan las características de OpenGL disponibles en la máquina:

	if (!glt::initialize_opengl_extensions())
	{
		exit (-1);
	}

    // Se activa la sincronización vertical:

    window.setVerticalSyncEnabled (true);

    // Se crea y se configura la escena:

	shared_ptr< Scene > scene(new Scene(dynamicsWorld.get()));
	shared_ptr< Tank  > tank (new Tank (dynamicsWorld.get(), scene));

     scene->configure_scene();

	

    // Se inicializan algunos elementos de OpenGL:

   // Scene reset_viewport (window);
	scene->reset_viewport(window);

    glClearColor (0.2f, 0.2f, 0.2f, 1.f);

    bool running = true;
    int  frame   = 0;

    do
    {
        // Read the user input:

        sf::Event event;

        while (window.pollEvent (event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    running = false;
                    break;
                }

                case sf::Event::Resized:
                {

					scene->reset_viewport(window);
                    break;
                }
            }
        }

        // Perform the simulation:

        dynamicsWorld->getWorld()->stepSimulation (1.f / 60.f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene->render();
		tank->update();

        window.display ();
    }
    while (running);

    // Se debe destruir el mundo físico antes de que se destruyan los cuerpos rígidos:

	dynamicsWorld.reset();

    return EXIT_SUCCESS;
}
