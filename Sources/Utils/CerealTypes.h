#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cereal
{
template<class T> class NameValuePair;
template<class T> NameValuePair<T> make_nvp(const char* name, T&& value);
}

#define CEREAL_SERIALIZATION(code) \
template<class Archive> void serialize(Archive& archive) code

#define CEREAL_LOAD(code) \
template<class Archive> void load(Archive& archive) code

#define CEREAL_SAVE(code) \
template<class Archive> void save(Archive& archive) code


template<class Archive>
void save(Archive& archive, const glm::vec3& m)
{
	archive(cereal::make_nvp("x", m.x),
		cereal::make_nvp("y", m.y),
		cereal::make_nvp("z", m.z));
}

template<class Archive>
void load(Archive& archive, glm::vec3& m)
{
	archive(cereal::make_nvp("x", m.x),
		cereal::make_nvp("y", m.y),
		cereal::make_nvp("z", m.z));
}

template<class Archive>
void save(Archive& archive, const glm::vec2& m)
{
	archive(m.x, m.y);
}

template<class Archive>
void load(Archive& archive, glm::vec2& m)
{
	archive(m.x, m.y);
}

template<class Archive>
void save(Archive& archive, const glm::vec4& m)
{
	archive(m.x, m.y, m.z, m.w);
}

template<class Archive>
void load(Archive& archive, glm::vec4& m)
{
	archive(m.x, m.y, m.z, m.w);
}
