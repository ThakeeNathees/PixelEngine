#pragma once
#include "..//core.h"


namespace pe
{
	// TODO: signals
	class PIXEL_ENGINE_API Area : public sf::Transformable
	{
	public:
		~Area();
		enum ShapeType
		{
			UNKNOWN = 0, RECTANGLE, CIRCLE, CONVEX_POLYGON,
		};

		// setter
		void setPosition(float x, float y);
		inline void setPosition(glm::fvec2 position) { setPosition(position.x, position.y); }
		inline void setPosition(const sf::Vector2f position) { setPosition(position.x, position.y); }
		void setRotation(float angle);
		void setScale(float x, float y);
		inline void setScale(glm::fvec2 scale) { setScale(scale.x, scale.y); }
		inline void setScale(const sf::Vector2f scale) { setScale(scale.x, scale.y); }

		void setShape( sf::RectangleShape* shape );
		void setShape( sf::CircleShape* shape );
		void setShape( sf::ConvexShape* shape );


		// getter
		bool contains( glm::fvec2 point );
		inline sf::Shape* getShape() { return m_shape; }
		inline ShapeType getShapeType() { return m_shape_type; }

	private:
		static void applyTransform(sf::Transformable* to, sf::Transformable* from);

		sf::Shape* m_shape;
		ShapeType m_shape_type = ShapeType::UNKNOWN;

	};


}