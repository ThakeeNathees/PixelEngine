#pragma once
#include "..//core.h"


#include "Asset.h"
#include "Sprite.h"
#include "Area.h"
#include "Signal.h"
#include "Animation.h"
#include "Timer.h"

#include "..//Assets.h"
#include "..//misc/Event.h"
#include "..//misc/Texture.h"
#include "..//misc/Drawable.h"

namespace pe
{
	// forward class declaration
	class Scene;
	class Application;


	class PIXEL_ENGINE_API Object : public sf::Transformable, public pe::Drawable, public Asset
	{
	public:
		Object();
		Object(const Object& other) = delete;
		~Object();

		// virtual functions
		inline virtual void init() {};
		inline virtual void process(double dt) {};
		inline virtual void input(Event& event) {} // return if event handled ?
		inline virtual void recieveSignal(Signal& signal) {}
		virtual void drawCall() const;
		void draw(const sf::Drawable& drawable) const;
	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void drawDebug(sf::RenderTarget& target)const;
	public:

		// draw methods
		sf::RenderTarget& getRenderTarget() const;
		void drawSelf() const;
		void drawRectangle(float x, float y, float width, float height, sf::Color color = m_default_color, bool outline = false, int outline_thickness = 2) const;

		template <typename T_position = glm::fvec2, typename T_dimension = glm::fvec2>
		void drawRectangle(const T_position & position, const T_dimension & dimension, sf::Color color = m_default_color, bool outline = false, int outline_thickness = 2) const { drawRectangle(position.x, position.y, dimension.x, dimension.y, color, outline, outline_thickness); }
		template <typename T = glm::fvec4>
		void drawRectangle(const T & rect, sf::Color color = m_default_color, bool outline = false, int outline_thickness = 2) const { drawRectangle(rect.x, rect.y, rect.z, rect.w, color, outline, outline_thickness); }
		inline void drawRectangle(const sf::FloatRect& rect, sf::Color color = m_default_color, bool outline = false, int outline_thickness = 2) const { drawRectangle(rect.top, rect.left, rect.width, rect.height, color, outline, outline_thickness); }
		inline void drawRectangle(const sf::RectangleShape& shape) { draw(shape); }


		void drawLine(float x1, float y1, float x2, float y2, float thickness = 5, sf::Color color = m_default_color)const; // TODO:	
		template <typename T_point1 = glm::fvec2, typename T_point2 = glm::fvec2>
		inline void drawLine(const T_point1 & point1, const T_point2 & point2, float thickness = 5, sf::Color color = m_default_color) const {
			drawLine(point1.x, point1.y, point2.x, point2.y, thickness, color);
		}

		void drawCircle(float x, float y, float r, sf::Color color = m_default_color, bool outline = false, int outline_thickness = 2) const;
		template < typename T = glm::fvec2 >
		inline void drawCircle(const T & position, float r, sf::Color color = m_default_color, bool outline = false, int outline_thickness = 2) const { drawCircle(position.x, position.y, r, color, outline, outline_thickness); }

		void emitSignal(Signal& signal);

		// setters
		void setPosition(float x, float y);
		template < typename T = glm::fvec2 >
		inline void setPosition(const T & position) { setPosition(position.x, position.y); }

		void setRotation(float angle);
		void setScale(float scale_x, float scale_y);
		template <typename T = glm::fvec2>
		void setScale(const T & scale) { setScale(scale.x, scale.y); }
		void setOrigin(float x, float y);
		template <typename T = glm::fvec2>
		inline void setOrigin(const T & position) { setOrigin(position.x, position.y); }


		void move(float x, float y);
		template <typename T = glm::fvec2>
		inline void move(const T & vect) { move(vect.x, vect.y); }
		void rotate(float angle);
		void scale(float x, float y);
		inline void scale(float x) { scale(x, x); }
		template <typename T = glm::fvec2>
		inline void scale(const T & vect) { scale(vect.x, vect.y); }

		void setSprite(Sprite* sprite);
		void setZIndex(int z_index);
		void setArea(Area* area = nullptr);
		void addAnimation(Animation* anim);
		void addTimer(Timer* timer);

		inline void setName(const std::string& name) override { m_name = name; }
		inline void setVisible(bool visible) { m_visible = visible; }
		inline void setPersistence(bool persistence) { m_persistence = persistence; }

		void clear(); // clear timers, ...

		// getters  TODO: getPosition<glm::fvec2>()
		inline const std::string& getName() const override { return m_name; }
		inline const std::string& getClassName() const { return m_class_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Object; }
		inline int getZIndex() const { return m_z_index; }
		inline bool getVisible() const { return m_visible; }
		inline bool getPersistence() const { return m_persistence; }

		inline Application& getApplication() const { assert(m_applicaton != nullptr); return *m_applicaton; }
		inline Scene& getScene() const { assert(m_scene != nullptr);		return *m_scene; }
		inline Area& getArea() const { assert(m_area != nullptr);		return *m_area; }
		inline Sprite& getSprite() const { assert(m_sprite != nullptr);		return *m_sprite; }
		inline std::vector<Timer*>& getTimers() { return m_timers; }
		Timer& getTimer(const std::string& timer_name);
		inline std::map<std::string, Animation*>& getAnimations() { return m_animations; }
		Animation& getAnimation(const std::string& anim_name);
		

		inline bool hasApplication() const { return m_applicaton != nullptr; }
		inline bool hasScene() const { return m_scene != nullptr; }
		inline bool hasArea() const { return m_area != nullptr; }
		inline bool hasSprite() const { return m_sprite != nullptr; }
		bool hasAnimation(const std::string& anim_name);
		bool hasTimer(const std::string& timer_name);




	private:
		inline void setScene(Scene* scene) { m_scene = scene; }
		friend class Scene;
		friend class Assets;
		friend class Application;
		friend class AssetsReader;
		
		static int s_object_count;
		static int s_next_id;
		static sf::RenderTarget* s_render_target; // const methods can edit static field

		

		std::string m_class_name; // class name as string
		std::string m_name;
		int m_id;
		int m_z_index = 0; // small val render first
		bool m_visible = true;
		bool m_persistence = false; // persistence between scenes
		Scene* m_scene = nullptr;
		Application* m_applicaton = nullptr;
		Sprite* m_sprite = nullptr;
		Area* m_area = nullptr;
		std::vector<Timer*> m_timers;
		std::map<std::string, Animation*> m_animations;

		// for debug printing
		static sf::Color m_default_color;
		sf::CircleShape* m_dbg_origin = nullptr;
	};
}