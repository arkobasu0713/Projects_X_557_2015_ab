//
//  main_spotlight.cpp
//  HCI 557 Spotlight example
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Sphere3D.h"
#include "GLAppearance.h"




using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;



int main(int argc, const char * argv[])
{


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Init glfw, create a window, and init glew

	// Init the GLFW Window
	window = initWindow();


	// Init the glew api
	initGlew();



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Create some models

	// coordinate system
	CoordSystem* cs = new CoordSystem(80.0);


	// create an apperance object.
	GLAppearance* apperance1 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance2 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance3 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance4 = new GLAppearance("../../data/shaders/multi_vertex_lights1.vs", "../../data/shaders/multi_vertex_lights1.fs");

	GLDirectLightSource  light_source1;
	light_source1._lightPos = glm::vec4(50.0, 10.0, 50.0, 0.0);
	light_source1._ambient_intensity = 0.0;
	light_source1._specular_intensity = 1.0;
	light_source1._diffuse_intensity = 1.0;
	light_source1._attenuation_coeff = 0.02;

	// add the spot light to this apperance object
	apperance1->addLightSource(light_source1);

	// Create a material object
	GLMaterial material1;
	material1._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
	material1._ambient_material = glm::vec3(0.0, 0.0, 1.0);
	material1._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material1._shininess = 100.0; // adjust the highlight to a smaller reflection. 

	// Add the material to the apperance object
	apperance1->setMaterial(material1);
	apperance1->finalize();

	// create the sphere geometry
	GLSphere3D* sphere1 = new GLSphere3D(-23.0, 0.0, 0.0, 5.0, 90, 50);
	sphere1->setApperance(*apperance1);
	sphere1->init();

	material1._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
	material1._ambient_material = glm::vec3(1.0, 0.0, 0.0);
	apperance1->updateMaterial();
	//light_source1._diffuse_intensity = 10.0;
	apperance1->updateLightSources();

	////////////////////////////// second obje1`ct 

	GLDirectLightSource  light_source2;
	light_source2._lightPos = glm::vec4(50.0, 10.0, 50.0, 0.0);
	light_source2._ambient_intensity = 0.0;
	light_source2._specular_intensity = 0.0;
	light_source2._diffuse_intensity = 1.0;
	light_source2._attenuation_coeff = 0.02;

	// add the spot light to this apperance object
	apperance2->addLightSource(light_source2);


	// Create a material object
	GLMaterial material2;
	material2._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
	material2._ambient_material = glm::vec3(0.0, 0.0, 1.0);
	material2._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material2._shininess = 12.0;

	// Add the material to the apperance object
	apperance2->setMaterial(material2);
	apperance2->finalize();

	// create the sphere geometry
	GLSphere3D* sphere2 = new GLSphere3D(-8.0, 0.0, 0.0, 5.0, 90, 50);
	sphere2->setApperance(*apperance2);
	sphere2->init();



	material2._diffuse_material = glm::vec3(0.0, 0.0, 1.0); // blue sphere
	material2._ambient_material = glm::vec3(0.0, 0.0, 1.0); // blue sphere
	apperance2->updateMaterial();
	light_source2._diffuse_intensity = 1.0;
	apperance2->updateLightSources();


	///////////////////////////////////// third sphere 

	// The spotlight object
	GLSpotLightSource  light_source3;
	light_source3._lightPos = glm::vec4(7.0, 3.5, 10.0, 1.0);
	light_source3._ambient_intensity = 0.0;
	light_source3._specular_intensity = 20.0;
	light_source3._diffuse_intensity = 10.0;
	light_source3._attenuation_coeff = 0.02;
	light_source3._cone_angle = 35.0; // in degree
	light_source3._cone_direction = glm::vec3(0.0, 0.0, -1.0); // this must be aligned with the object and light position.


	// add the spot light to this apperance object
	apperance3->addLightSource(light_source3);

	// Create a material object
	GLMaterial material3;
	material3._diffuse_material = glm::vec3(0.0, 1.0, 0.0);
	material3._ambient_material = glm::vec3(0.0, 1.0, 0.0);
	material3._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material3._shininess = 150.0;

	// Add the material to the apperance object
	apperance3->setMaterial(material3);
	apperance3->finalize();

	// create the sphere geometry
	GLSphere3D* sphere3 = new GLSphere3D(7.0, 0.0, 0.0, 5.0, 100, 150);
	sphere3->setApperance(*apperance3);
	sphere3->init();



	material3._diffuse_material = glm::vec3(0.0, 1.0, 0.0);
	material3._ambient_material = glm::vec3(0.0, 1.0, 0.0);
	apperance3->updateMaterial();
	light_source3._specular_intensity = 20.0;
	apperance3->updateLightSources();

	/////////////////////////////////// fourth sphere

	// The spotlight object
	GLSpotLightSource  light_source4;
	light_source4._lightPos = glm::vec4(20.0, 3.5, 10.0, 1.0);
	light_source4._ambient_intensity = 0.4;
	light_source4._specular_intensity = 0.9;
	light_source4._diffuse_intensity = 0.9;
	light_source4._attenuation_coeff = 0.02;
	light_source4._cone_angle = 35.0; // in degree
	light_source4._cone_direction = glm::vec3(0.0, 0.0, -1.0); // this must be aligned with the object and light position.


	GLDirectLightSource  light_source5;
	light_source5._lightPos = glm::vec4(-13.0, -5.0, 10.0, 0.0); //25,0,20,15
	light_source5._ambient_intensity = 0.0;
	light_source5._specular_intensity = 0.0;
	light_source5._diffuse_intensity = 1.0;
	light_source5._attenuation_coeff = 0.02;


	// add the spot light to this apperance object
	apperance4->addLightSource(light_source4);
	apperance4->addLightSource(light_source5);

	// Create a material object
	GLMaterial material4;
	material4._diffuse_material = glm::vec3(0.5, 0.5, 0.1);
	material4._ambient_material = glm::vec3(0.5, 0.5, 0.1);
	material4._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material4._shininess = 150.0;

	// Add the material to the apperance object
	apperance4->setMaterial(material4);
	apperance4->finalize();

	// create the sphere geometry
	GLSphere3D* sphere4 = new GLSphere3D(20.0, 0.0, 0.0, 5.0, 90, 50);
	sphere4->setApperance(*apperance4);
	sphere4->init();

	material4._diffuse_material = glm::vec3(1.0, 1.0, 0.0);
	material4._ambient_material = glm::vec3(1.0, 1.0, 0.0);
	apperance4->updateMaterial();
	//light_source4._diffuse_intensity = 0.1;
	apperance4->updateLightSources();



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Main render loop

	// Set up our green background color
	static const GLfloat clear_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// This sets the camera to a new location
	// the first parameter is the eye position, the second the center location, and the third the up vector. 
	SetViewAsLookAt(glm::vec3(12.0f, 12.0f, 35.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	// Enable depth test
	// ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	// sphere->enableNormalVectorRenderer();

	// This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
	while (!glfwWindowShouldClose(window))
	{

		// Clear the entire buffer with our green color (sets the background to be green).
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//// This renders the objects

		// Set the trackball locatiom
		SetTrackballLocation(trackball.getRotationMatrix());

		// draw the objects
		cs->draw();

		sphere1->draw();
		sphere2->draw();
		sphere3->draw();
		sphere4->draw();

		//// This renders the objects
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		// Swap the buffers so that what we drew will appear on the screen.
		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	delete cs;


}

