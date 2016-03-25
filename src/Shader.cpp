//
//  Shader.cpp
//  dyne
//
//  Created by Elliot Patros on 3/21/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Shader.h"

const string Shader::glslPath {"glsl_source/"};

Shader::Shader(void)
{
    programId = 0;
}

Shader::Shader(const string vsDir, const string fsDir)
{
    // get source code from file
    ifstream vsFileStream(glslPath + vsDir);
    ifstream fsFileStream(glslPath + fsDir);
    const string svsCode((istreambuf_iterator<char>(vsFileStream)),
                         istreambuf_iterator<char>());
    const string sfsCode((istreambuf_iterator<char>(fsFileStream)),
                         istreambuf_iterator<char>());
    vsFileStream.close();
    fsFileStream.close();
    const GLchar* vsCode(svsCode.c_str());
    const GLchar* fsCode(sfsCode.c_str());
    
    // compile shaders
    const GLuint vsId(glCreateShader(GL_VERTEX_SHADER));
    glShaderSource(vsId, 1, &vsCode, NULL);
    glCompileShader(vsId);
    checkCompileError(vsId);
    
    const GLuint fsId(glCreateShader(GL_FRAGMENT_SHADER));
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
    const unsigned logSize(512);
    GLchar infoLog[logSize];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, logSize, NULL, infoLog);
        post("shader failed to compile: ", infoLog);
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
    const unsigned logSize(512);
    GLchar infoLog[logSize];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog (program, logSize, NULL, infoLog);
        post("shader failed to link: ", infoLog);
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
