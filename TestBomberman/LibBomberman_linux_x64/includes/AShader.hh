	#pragma once

#include <OpenGL.hh>
#include <string>
#include <glm/glm.hpp>

namespace	gdl
{
	// Represents an abstract shader
	class AShader
	{
	public:
		enum SHADER_TYPE
		{
			VERTEX_SHADER
			, FRAGMENT_SHADER
			, GEOMETRY_ID
		};
	public:
		AShader();
		virtual ~AShader();
		// Bind the shader as the current used shader
		void bind();
		// Get the OpenGL program ID
		GLuint getProgramId() const;
		// Load a vertex or a fragment shader from a file
		bool load(const std::string &path, GLenum type);
		// Get the location of a constant variable in the shader
		GLuint getUniformId(const std::string &k) const;

		// Setters for the different kind of constant variables
		bool setUniform(const std::string &k, glm::vec2 const &v) const;
		bool setUniform(const std::string &k, glm::vec3 const &v) const;
		bool setUniform(const std::string &k, glm::vec4 const &v) const;
		bool setUniform(const std::string &k, glm::mat2 const &v) const;
		bool setUniform(const std::string &k, glm::mat3 const &v) const;
		bool setUniform(const std::string &k, glm::mat4 const &v) const;
		bool setUniform(const std::string &k, glm::ivec2 const &v) const;
		bool setUniform(const std::string &k, glm::ivec3 const &v) const;
		bool setUniform(const std::string &k, glm::ivec4 const &v) const;
		bool setUniform(const std::string &k, glm::uvec2 const &v) const;
		bool setUniform(const std::string &k, glm::uvec3 const &v) const;
		bool setUniform(const std::string &k, glm::uvec4 const &v) const;
		bool setUniform(const std::string &k, float v) const;
		bool setUniform(const std::string &k, unsigned int v) const;
		bool setUniform(const std::string &k, int v) const;
		bool setUniform(const std::string &k, double v) const;

		// Build and link the shader (using _compileShader and _link) and bind the locations of the attributes and samplers
		virtual bool build() = 0;

	protected:
		void _build();

		// Compile the shader
		bool _compileShader(GLuint shaderId, std::string const &file) const;
		// Link the program
		bool _linkProgram();
		// Bind a shader attribute to a location
		void _bindAttribLocation(GLuint location, std::string const &attribName);
		// Bind a sampler to the binding point texUnit
		bool _bindTextureUnit(GLuint texUnit, std::string const &samplerName);

	private:
		GLuint _programId;
		GLuint _vertexId;
		GLuint _fragmentId;
		GLuint _geoId;
	};

}