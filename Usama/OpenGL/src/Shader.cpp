#include "../inc/Shader.h"
ShaderManager* ShaderManager::instance;
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glUseProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void ShaderManager::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

bool ShaderManager::i_GenerateAllShaders()
{

    std::vector<std::string> simpleshader;
    simpleshader.push_back("Shaders/SimpleShader.vert");
    simpleshader.push_back("Shaders/SimpleShader.frag");
    i_GenerateShader(simpleshader, SIMPLESHADER);

    std::vector<std::string> ParticleShader;
    ParticleShader.push_back("Shaders/ParticleShader.vert");
    ParticleShader.push_back("Shaders/ParticleShader.frag");
    i_GenerateShader(ParticleShader, PARTICLESHADER);

    std::vector<std::string> LightCubeShader;
    LightCubeShader.push_back("Shaders/LightCubeShader.vert");
    LightCubeShader.push_back("Shaders/LightCubeShader.frag");
    i_GenerateShader(LightCubeShader, LIGHTCUBESHADER);


    std::vector<std::string> DiffuseShader;
    DiffuseShader.push_back("Shaders/DiffuseShader.vert");
    DiffuseShader.push_back("Shaders/DiffuseShader.frag");
    i_GenerateShader(DiffuseShader, DIFFUSESHADER);

    i_SetUpLocation();
    return true;
}

bool ShaderManager::i_GenerateShader(std::vector<std::string> shader, e_ShaderType shadertype)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(shader.at(0).c_str());
        fShaderFile.open(shader.at(1).c_str());
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    GLuint s_ID;
    s_ID = glCreateProgram();
    glAttachShader(s_ID, vertex);
    glAttachShader(s_ID, fragment);
    glLinkProgram(s_ID);
    glUseProgram(s_ID);
    checkCompileErrors(s_ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    allTheShaders[shadertype].WhichType[e_ShaderLocationType::ID] = s_ID;




    // allShaders[shadertype] = ID;
    return false;
}

bool ShaderManager::i_SetUpLocation()
{
    //Particle shader
    allTheShaders[PARTICLESHADER].WhichType[e_ShaderLocationType::PROJ]  = glGetUniformLocation(allTheShaders.at(PARTICLESHADER).WhichType.at(ID), "projection");
    allTheShaders[PARTICLESHADER].WhichType[e_ShaderLocationType::VIEW]  = glGetUniformLocation(allTheShaders.at(PARTICLESHADER).WhichType.at(ID), "view");
    allTheShaders[PARTICLESHADER].WhichType[e_ShaderLocationType::MODEL] = glGetUniformLocation(allTheShaders.at(PARTICLESHADER).WhichType.at(ID), "model");
    allTheShaders[PARTICLESHADER].WhichType[e_ShaderLocationType::COLOR] = glGetUniformLocation(allTheShaders.at(PARTICLESHADER).WhichType.at(ID), "color");

    //Basic shader
    allTheShaders[SIMPLESHADER].WhichType[e_ShaderLocationType::VIEW]    = glGetUniformLocation(allTheShaders.at(SIMPLESHADER).WhichType.at(ID),   "view");
    allTheShaders[SIMPLESHADER].WhichType[e_ShaderLocationType::PROJ]    = glGetUniformLocation(allTheShaders.at(SIMPLESHADER).WhichType.at(ID),   "projection");
    allTheShaders[SIMPLESHADER].WhichType[e_ShaderLocationType::COLOR]   = glGetUniformLocation(allTheShaders.at(SIMPLESHADER).WhichType.at(ID),   "color");
    allTheShaders[SIMPLESHADER].WhichType[e_ShaderLocationType::MODEL]   = glGetUniformLocation(allTheShaders.at(SIMPLESHADER).WhichType.at(ID),   "model");

    //Light Cube Shader
    allTheShaders[LIGHTCUBESHADER].WhichType[e_ShaderLocationType::PROJ] = glGetUniformLocation(allTheShaders.at(LIGHTCUBESHADER).WhichType.at(ID), "projection");
    allTheShaders[LIGHTCUBESHADER].WhichType[e_ShaderLocationType::VIEW] = glGetUniformLocation(allTheShaders.at(LIGHTCUBESHADER).WhichType.at(ID), "view");
    allTheShaders[LIGHTCUBESHADER].WhichType[e_ShaderLocationType::MODEL] = glGetUniformLocation(allTheShaders.at(LIGHTCUBESHADER).WhichType.at(ID), "model");
    allTheShaders[LIGHTCUBESHADER].WhichType[e_ShaderLocationType::COLOR] = glGetUniformLocation(allTheShaders.at(LIGHTCUBESHADER).WhichType.at(ID), "color");
   
    //Diffuse Shader
    allTheShaders[DIFFUSESHADER].WhichType[e_ShaderLocationType::PROJ] = glGetUniformLocation(allTheShaders.at(DIFFUSESHADER).WhichType.at(ID), "projection");
    allTheShaders[DIFFUSESHADER].WhichType[e_ShaderLocationType::VIEW] = glGetUniformLocation(allTheShaders.at(DIFFUSESHADER).WhichType.at(ID), "view");
    allTheShaders[DIFFUSESHADER].WhichType[e_ShaderLocationType::MODEL] = glGetUniformLocation(allTheShaders.at(DIFFUSESHADER).WhichType.at(ID), "model");
    allTheShaders[DIFFUSESHADER].WhichType[e_ShaderLocationType::COLOR] = glGetUniformLocation(allTheShaders.at(DIFFUSESHADER).WhichType.at(ID), "color");       
    allTheShaders[DIFFUSESHADER].WhichType[e_ShaderLocationType::LIGHTPOS] = glGetUniformLocation(allTheShaders.at(DIFFUSESHADER).WhichType.at(ID), "lightPos");    
    allTheShaders[DIFFUSESHADER].WhichType[e_ShaderLocationType::CAMERAPOS] = glGetUniformLocation(allTheShaders.at(DIFFUSESHADER).WhichType.at(ID), "viewPos");   
    return false;
}

void ShaderManager::InitShaderManager()
{
    instance = new ShaderManager();
    instance->i_GenerateAllShaders();
}

GLuint ShaderManager::GetShaderID(e_ShaderType shaderType)
{
    return instance->allTheShaders.at(shaderType).WhichType.at(ID);
}

ShaderIDLocations ShaderManager::GetShaderLocations(e_ShaderType shaderType)
{
    return instance->allTheShaders.at(shaderType);
}