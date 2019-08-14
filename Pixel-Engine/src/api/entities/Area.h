#pragma once
#include "..//core.h"


namespace pe
{
	// TODO: signals
	class PIXEL_ENGINE_API Area
	{
	public:
		~Area();
		enum ShapeType
		{
			UNKNOWN = 0, RECTANGLE, CIRCLE, CONVEX_POLYGON,
		};

		// setter
		void setShape( sf::RectangleShape* shape );
		void setShape( sf::CircleShape* shape );
		void setShape( sf::ConvexShape* shape );


		// getter
		bool contains( glm::fvec2 point );
		inline sf::Shape* getShape() { return m_shape; }
		inline ShapeType getShapeType() { return m_shape_type; }

	private:
		sf::Shape* m_shape;
		ShapeType m_shape_type = ShapeType::UNKNOWN;

	};


}