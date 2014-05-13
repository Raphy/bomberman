#pragma once

#include <AShader.hh>
#include <vector>

#include <glm/glm.hpp>

namespace gdl
{
	class VertexBuffer;

	// Class used to create raw geometry by pushing vertex informations
	class Geometry
	{
	public:
		Geometry();
		~Geometry();

		// Push a vertice
		Geometry &pushVertex(const glm::vec3 &t);
		// Push a UV texture coordinate
		Geometry &pushUv(const glm::vec2 &t);
		// Push a normal
		Geometry &pushNormal(const glm::vec3 &t);
		// Push a color
		Geometry &setColor(const glm::vec4 &t);

		// Build the geometry, must be called once
		bool build();
		// Draw the geometry, the build function must have been called before
		void draw(AShader &shader, glm::mat4 const &transform, GLenum drawMode);

	private:
		VertexBuffer			*_buffer;
		std::vector<glm::vec4>	_vertices;
		std::vector<glm::vec4>	_colors;
		std::vector<glm::vec4>	_normals;
		std::vector<glm::vec2>	_uvs;

		glm::vec4				_currentColor;
	};
}