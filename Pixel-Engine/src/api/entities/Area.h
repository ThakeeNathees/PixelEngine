#pragma once
#include "..//core.h"

#include "..//utils/math_utils.h"
#include "Asset.h"

namespace pe
{
	class PIXEL_ENGINE_API Area : public sf::Shape, public Asset
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

		inline void setName(const std::string& name) override { m_name = name; }
		void setShape(sf::Shape* shape);


		// getter
		const std::string& getName() const override { return m_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Area; }

		std::size_t getPointCount() const override;
		sf::Vector2f getPoint(std::size_t index) const override;

		inline sf::Vector2f getCentroid(bool local = false) const {
			if (local) return m_centroid;
			return applyTransform<sf::Vector2f, sf::Vector2f>(m_centroid, *this);
		}

		bool isContains(float x, float y);
		inline bool isConvex() const{ return m_is_convex; }
		inline bool isContains(glm::fvec2 point) { return isContains(point.x, point.y); }
		inline bool isContains(sf::Vector2f point) { return isContains(point.x, point.y); }
		inline bool isIntersecting(const Area& other) { return ::pe::isIntersecting( getShape(), other.getShape() ); }

		inline bool hasShape() { return m_shape != nullptr; }

		inline sf::Shape& getShape() const { assert( hasShape() && "shape is nullptr" ); return *m_shape; }
		inline bool hasShape() const { return m_shape != nullptr; }

	private:
		friend class AssetsReader;

		std::string m_name;
		static int s_area_count;
		static int s_next_id;
		int m_id;
		sf::Vector2f m_centroid;
		bool m_is_convex = false;
		sf::Shape* m_shape = nullptr;
		sf::Color m_fill_color = sf::Color(50, 75, 100, 100); // for debug
	};


}