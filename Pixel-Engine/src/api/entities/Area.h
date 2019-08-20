#pragma once
#include "..//core.h"

#include "..//..//utils/math_utils.h"

namespace pe
{
	// TODO: signals
	class PIXEL_ENGINE_API Area : public sf::Shape
	{
	public:
		inline Area() {}
		Area(const Area& other) = delete;
		~Area();

		// setter
		void setPosition(float x, float y);
		template <typename T = glm::fvec2>
		inline void setPosition(const T & position) { setPosition(position.x, position.y); }
		void setRotation(float angle);
		void setScale(float x, float y);
		template <typename T = glm::fvec2>
		inline void setScale(const T & scale) { setScale(scale.x, scale.y); }


		void move(float x, float y);
		template <typename T = glm::fvec2>
		void move(const T & vect) { move(vect.x, vect.y); }
		void rotate(float angle);
		void scale(float x, float y);
		template <typename T = glm::fvec2>
		void scale(const T & vect) { scale(vect.x, vect.y); }
		void setOrigin(float x, float y);
		template <typename T = glm::fvec2>
		void setOrigin(const T & position) { setOrigin(position.x, position.y); }

		void setShape(sf::Shape* shape);


		// getter
		std::size_t getPointCount() const override;
		sf::Vector2f getPoint(std::size_t index) const override;

		inline sf::Vector2f getCentre(bool local = false) const {
			if (local) return m_centroid;
			return applyTransform<sf::Vector2f, sf::Vector2f>(m_centroid, *this);
		}

		bool isContains(int x, int y);
		inline bool isContains(glm::ivec2 point) { return isContains(point.x, point.y); }
		inline bool isContains(sf::Vector2i point) { return isContains(point.x, point.y); }
		// TODO: bool isIntersect( const Area& another_area );

		inline sf::Shape& getShape() const { assert(m_shape != nullptr); return *m_shape; }
		inline bool hasShape() const { return m_shape != nullptr; }

	private:
		sf::Vector2f m_centroid;
		bool m_is_convex = false;
		sf::Shape* m_shape = nullptr;
		sf::Color m_fill_color = sf::Color(50, 75, 100, 100);
	};


}