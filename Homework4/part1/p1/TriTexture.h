//
//  TriTexture.hpp
//
//  Group:
//  Brian R., breber@iastate.edu
//  Arko B., abasu@iastate.edu
//  Sindhusha D., dsindhu@iastate.edu

#pragma once

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// locals
#include "GLAppearanceBase.h"
#include "Texture.h"

class TriTexture : public GLTextureBase
{
private:
    // Allow the class GLApperance access to protected variables.
    friend class GLAppearance;

    // These are the variable names which are used in our glsl shader programs.
    // Make sure that you use the correct names in your programs.
    const string      _glsl_names[3] = { "texture1", "texture2", "texture3"};

public:
    TriTexture();
    ~TriTexture();

    /*!
     Load two bitmap images as textures from files.
     @param path_and_file_texture_1 - path and file of the first image.
     @param path_and_file_texture_1 - path and file of the second image.
     @return int - the texture id when the texture was sucessfully loaded.
     */
    int loadAndCreateTextures(
        string path_and_file_texture_1,
        string path_and_file_texture_2,
        string path_and_file_texture_3);

    /*!
     Adds the variables of this object to the shader program
     */
    virtual bool addVariablesToProgram(GLuint program, int variable_index);

    virtual bool dirty(GLuint program) {
        return true;
    }

private:
    // The texture for this program.
    GLuint      _texture_1;
    GLuint      _texture_2;
    GLuint      _texture_3;

    // location of the texture in the glsl program
    int         _textureIdx1;
    int         _textureIdx2;
    int         _textureIdx3;
};
