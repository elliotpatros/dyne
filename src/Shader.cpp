//
//  Shader.cpp
//  dyne
//
//  Created by Elliot Patros on 3/21/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Shader.h"

const string Shader::glslPath ("glsl/");

Shader::Shader(void)
{
    programId = 0;
}

Shader::Shader(const string vsDir, const string fsDir)
{
    string svsCode, sfsCode;
    
    try
    {
        // get source code from file
        ifstream vsFileStream(glslPath + vsDir);
        ifstream fsFileStream(glslPath + fsDir);
        svsCode = string((istreambuf_iterator<char>(vsFileStream)),
                          istreambuf_iterator<char>());
        sfsCode = string((istreambuf_iterator<char>(fsFileStream)),
                          istreambuf_iterator<char>());
        vsFileStream.close();
        fsFileStream.close();
    }
    catch (ifstream::failure error)
    {
        IO::post("shader ifstream failed", error.what());
    }
    
    const GLchar* vsCode (svsCode.c_str());
    const GLchar* fsCode (sfsCode.c_str());
    
    // compile shaders
    const GLuint vsId (glCreateShader(GL_VERTEX_SHADER));
    glShaderSource(vsId, 1, &vsCode, NULL);
    glCompileShader(vsId);
    checkCompileError(vsId);
    
    const GLuint fsId (glCreateShader(GL_FRAGMENT_SHADER));
    glShaderSource(fsId, 1, &fsCode, NULL);
    glCompileShader(fsId);
    checkCompileError(fsId);
    
    // link shaders
    programId = glCreateProgram();
    glAttachShader(programId, vsId);
    glAttachShader(programId, fsId);
    glLinkProgram(programId);
    checkLinkingError(programId);
    
    // clean up
    glDeleteShader(vsId);
    glDeleteShader(fsId);
}


bool Shader::checkCompileError(const GLuint shader) const noexcept
{
    // returns true if error
    GLint success;
    const unsigned logSize (512);
    GLchar infoLog[logSize];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, logSize, NULL, infoLog);
        IO::post("shader failed to compile: ", infoLog);
        return true;
    }
    else
    {
        return false;
    }
}

bool Shader::checkLinkingError(const GLuint program) const noexcept
{
    GLint success;
    const unsigned logSize (512);
    GLchar infoLog[logSize];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog (program, logSize, NULL, infoLog);
        IO::post("shader failed to link: ", infoLog);
        return true;
    }
    else
    {
        return false;
    }
}

void Shader::use(void) const noexcept
{
    glUseProgram(programId);
}

GLuint Shader::getId(void) const noexcept
{
    return programId;
}

GLuint Shader::useAndGetId(void) const noexcept
{
    glUseProgram(programId);
    return programId;
}
