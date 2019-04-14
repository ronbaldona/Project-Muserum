// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	float rad = glm::radians(degrees);
	mat3 a_star = mat3(0, axis[2], -axis[1],
					   -axis[2], 0, axis[0],
					   axis[1], -axis[0], 0);
	mat3 a_at = mat3(axis[0] * axis[0], axis[0] * axis[1], axis[0] * axis[2],
					 axis[0] * axis[1], axis[1] * axis[1], axis[1] * axis[2],
					 axis[0] * axis[2], axis[1] * axis[2], axis[2] * axis[2]);

	return (cos(rad) * mat3()) + (a_at * (1 - cos(rad))) + (sin(rad) * a_star);
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	mat3 rot = rotate(degrees, up);
	eye = rot * eye;
	up = rot * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	mat3 rot = rotate(degrees, glm::normalize(glm::cross(eye, up)));
	eye = rot * eye;
	up = rot * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	// Rotation coordinate frame
	vec3 w = glm::normalize(eye - center);
	vec3 u = glm::cross(glm::normalize(up), w);
	vec3 v = glm::cross(w, u);
	mat4 r = glm::transpose(mat4(vec4(u, 0),
								 vec4(v, 0),
								 vec4(w, 0),
								 vec4(0, 0, 0, 1)));

	// Translation matrix
	mat4 t = mat4(1, 0, 0, 0,
				  0, 1, 0, 0,
				  0, 0, 1, 0,
				  -eye[0], -eye[1], -eye[2], 1);

	// Matrices in glm are specified as col major
	return r * t;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float d = 1 / tan(glm::radians(fovy / 2));
	float A = -(zFar + zNear) / (zFar - zNear);
	float B = -2 * zFar * zNear / (zFar - zNear);
	mat4 ret = mat4(d / aspect, 0, 0, 0,
					0, d, 0, 0,
					0, 0, A, -1,
					0, 0, B, 0);
	return mat4(d / aspect, 0, 0, 0,
				0, d, 0, 0,
				0, 0, A, -1,
				0, 0, B, 0);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	return mat4(sx, 0, 0, 0,
				0, sy, 0, 0,
				0, 0, sz, 0,
				0, 0, 0, 1);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    return mat4(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				tx, ty, tz, 1);
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
