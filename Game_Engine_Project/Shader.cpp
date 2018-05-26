#include "Shader.h"
#include "Tools.h"


void Shader::UseShader()
{
	glUseProgram(shaderid_);
}

void Shader::SetBool(std::string name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderid_, name.c_str()), value);
}

void Shader::SetInt(std::string name, int value)
{
	glUniform1i(glGetUniformLocation(shaderid_, name.c_str()), value);
}

void Shader::SetFLoat(std::string name, float value)
{
	glUniform1f(glGetUniformLocation(shaderid_, name.c_str()), value);
}

void Shader::SetVec3(std::string name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(shaderid_, name.c_str()), value.x, value.y, value.z);
}

void Shader::SetVec3Array(std::string name, glm::vec3 v[])
{
	//glUniform3fv(glGetUniformLocation(shaderid_, name.c_str()), v->length(), v);
}

void Shader::destroy()
{
	glDeleteProgram(shaderid_);
}

Shader::Shader()
{
}

Shader::Shader(const Shader * shader)
{
	shaderlocations = shader->shaderlocations;
	shaderid_ = shader->shaderid_;
}

Shader::Shader(const char * vertex_file_path, const char * fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		Debug("Impossible to open " << vertex_file_path << ". Are you in the right directory ? Don't forget to read the FAQ !\n" << std::endl);
		getchar();
		return;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;



	// Compile Vertex Shader
	Debug("Compiling shader : " << vertex_file_path << std::endl );
	char const * VertexSourcePointer = VertexShaderCode.c_str();

	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);

	if (!Result) {
		int InfoLogLength;
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		Debug( &VertexShaderErrorMessage[0] << std::endl);
	}



	// Compile Fragment Shader
	Debug("Compiling shader : "<< fragment_file_path << std::endl);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();

	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);

	if (!Result) {
		int InfoLogLength;
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		Debug(&FragmentShaderErrorMessage[0] << std::endl);
	}



	// Link the program
	Debug("Linking program" << std::endl);
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);

	if (!Result) {
		int InfoLogLength;
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		Debug(&ProgramErrorMessage[0] << std::endl);
	}

	shaderid_ = ProgramID;
	//glDetachShader(ProgramID, VertexShaderID);
	//glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	shaderlocations.modelmatrixloc = glGetUniformLocation(shaderid_, "modelMatrix");
	shaderlocations.viewmatrixloc = glGetUniformLocation(shaderid_, "viewMatrix");
	shaderlocations.projectionmatrixloc = glGetUniformLocation(shaderid_, "projectionMatrix");
	shaderlocations.normalmatrixloc = glGetUniformLocation(shaderid_, "normalMatrix");
}


Shader::~Shader()
{
	//glDeleteProgram(shaderid_);
}
