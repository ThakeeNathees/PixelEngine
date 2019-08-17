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
		void setPosition(float x, float y) ;
		inline void setPosition(glm::fvec2 position) { setPosition(position.x, position.y); }
		inline void setPosition(const sf::Vector2f position) { setPosition(position.x, position.y); }
		void setRotation(float angle);
		void setScale(float x, float y);
		inline void setScale(glm::fvec2 scale) { setScale(scale.x, scale.y); }
		inline void setScale(const sf::Vector2f scale) { setScale(scale.x, scale.y); }

		void move(float x, float y);
		inline void move(sf::Vector2f vect) { move(vect.x, vect.y); }
		inline void move(glm::fvec2 vect) { move(vect.x, vect.y); }
		void rotate(float angle);
		void scale(float x, float y);
		inline void scale(sf::Vector2f vect) { scale(vect.x, vect.y); }
		inline void scale(glm::fvec2 vect) { scale(vect.x, vect.y); }

		void setShape( sf::Shape* shape );
		

		// getter
		std::size_t getPointCount() const override;
		sf::Vector2f getPoint(std::size_t index) const override;

		bool isContains( int x, int y );
		inline bool isContains(glm::ivec2 point) { return isContains(point.x, point.y); }
		inline bool isContains(sf::Vector2i point) { return isContains(point.x, point.y); }
		// TODO: bool isIntersect( const Area& another_area );

		inline sf::Shape& getShape() const { assert(m_shape!=nullptr); return *m_shape; }
		inline bool hasShape() const { return m_shape != nullptr; }

	private:
		sf::Shape* m_shape = nullptr;
		sf::Color m_fill_color = sf::Color(50, 75, 100, 100);

	};


}