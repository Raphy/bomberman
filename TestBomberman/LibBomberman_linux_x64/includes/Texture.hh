#pragma once

#include <string>
#include <OpenGL.hh>
#include <glm/glm.hpp>

namespace	gdl
{
	// Class representing an OpenGL texture
	class Texture
	{
	public:
		Texture();
		Texture(Texture const &o);
		virtual ~Texture();

		// Load a TGA file
		bool load(const std::string &path, bool genMimaps = false);

		// Returns the OpenGL texture ID
		GLuint getId() const;

		// Bind the texture as the current used texture
		void bind() const;

		// Get the dimensions of the texture
		GLuint getWidth() const;
		GLuint getHeight() const;

		Texture		&operator=(Texture const &o);

	protected:
		GLuint _width;
		GLuint _height;
		GLuint _id;
	};

}
