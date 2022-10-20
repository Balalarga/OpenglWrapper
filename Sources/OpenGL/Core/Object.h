#pragma once

class Texture2d;
class Shader;
class Geometry;

class Object
{
public:
	Object(Geometry* _geometry, Shader* _shader, Texture2d* _texture = nullptr);


	virtual void Render();
	
	
private:
	Geometry* _geometry;
	Shader* _shader;
	Texture2d* _texture;
};
