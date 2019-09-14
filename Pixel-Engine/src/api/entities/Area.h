#pragma once
#include "..//core.h"

#include "..//utils/math_utils.h"
#include "Asset.h"

namespace pe
{
	class PIXEL_ENGINE_API Area : public sf::Transformable, public Asset
	{
	public:
		inline Area() {
			s_area_count++;
			m_id = s_next_id++;
			m_name = std::string( "area_").append( std::to_string(m_id));
		}
		inline Area(const std::string& name): m_name(name) {
			s_area_count++;
			m_id = s_next_id++;
		}
		Area(const Area& other) = delete;
		~Area(); // deleted by object;

		// setter
		void setPosition(float x, float y);
		inline void setPosition(const sf::Vector2f& position) { setPosition(position.x, position.y); }
		void setRotation(float angle);
		void setScale(float x, float y);
		inline void setScale(const sf::Vector2f& scale) { setScale(scale.x, scale.y); }
		void setOrigin(float x, float y);
		void setOrigin(const sf::Vector2f& position) { setOrigin(position.x, position.y); }

		void move(float x, float y);
		void move(const sf::Vector2f& vect) { move(vect.x, vect.y); }
		void rotate(float angle);
		void scale(float x, float y);
		void scale(const sf::Vector2f& vect) { scale(vect.x, vect.y); }

		inline void setName(const std::string& name) override { m_name = name; }
		void setShape(sf::Shape* shape);


		// getter
		const std::string& getName() const override { return m_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Area; }
		inline static int getCount() { return s_area_count; }

		//std::size_t getPointCount() const override;
		//sf::Vector2f getPoint(std::size_t index) const override;

		inline sf::Vector2f getCentroid(bool local = false) const {
			assert( m_shape != nullptr );
			if (local) return m_centroid;
			return m_shape->getTransform().transformPoint(m_centroid);
		}

		bool isContains(float x, float y);
		inline bool isContains(const sf::Vector2f& point) { return isContains(point.x, point.y); }
		inline bool isConvex() const{ return m_is_convex; }
		inline bool isIntersecting(const Area& other) { return ::pe::isIntersecting( getShape(), other.getShape() ); }


		inline sf::Shape& getShape() const { assert(m_shape); return *m_shape; }
		inline bool hasShape() const { return m_shape != nullptr; }

	private:
		friend class FileHandler;

		std::string m_name;
		static int s_area_count;
		static int s_next_id;
		int m_id;
		sf::Vector2f m_centroid;
		bool m_is_convex = false;
		sf::Shape* m_shape = nullptr;
		static sf::Color s_debug_shape_color;
		static float s_outline_thickness;
	};


}