#include "pch.h"
#include "../Application.h"

#include "../utils/AssetsWriter.h"
#include "../utils/AssetsReader.h"

namespace pe
{
	
	// static initialization
	int Object::s_object_count = 0;
	int Object::s_next_id = static_cast<int>( Asset::Type::Object );
	sf::RenderTarget* Object::s_render_target = nullptr;
	sf::Color Object::m_default_color = sf::Color(50, 75, 100, 255);

	Object::Object() {
		s_object_count++;
		m_id = s_next_id++;
		m_name = std::string( "obj_").append(std::to_string(m_id));
		m_dbg_origin = new sf::CircleShape(3);
		m_dbg_origin->setFillColor(sf::Color(150, 75, 150, 200));
	}
	Object::~Object() {
		s_object_count--;
		if (m_dbg_origin)	delete m_dbg_origin;
		for (Timer* timer : m_timers) delete timer;
	}


	// virtual function
	void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		s_render_target = &target; // TODO: multiple viwe case
		drawCall();
		drawDebug(target);
		s_render_target = nullptr;
	}
	void Object::drawCall() const {
		drawSelf();
	}
	void Object::drawDebug(sf::RenderTarget& target) const {
		if (m_applicaton != nullptr && m_applicaton->isDebugMode()) {
			if (m_applicaton->isDebugDrawArea()) {
				if (m_area && m_area->hasShape()) {
					target.draw((m_area->getShape()));
					drawCircle(m_area->getCentroid(), 3, sf::Color(0, 255, 0, 255));
				}
			}

			if (m_dbg_origin) {
				m_dbg_origin->setPosition(getPosition());
				target.draw(*m_dbg_origin);
			}
		}
	}
	void Object::draw(const sf::Drawable& drawable) const {
		assert(s_render_target != nullptr && "draw(const sf::Drawable&) can only be call from draw() method");
		s_render_target->draw(drawable);
	}

	void Object::drawSelf() const {
		assert(s_render_target != nullptr && "drawself() can only be call from draw() method");
		if ( m_sprite ) s_render_target->draw(getSprite());
	}

	void Object::drawRectangle(float x, float y, float width, float height, sf::Color color, bool outline, int outline_thickness) const {
		assert(s_render_target != nullptr && "drawRectangle() can only be call from draw() method");
		sf::RectangleShape shape(sf::Vector2f(width, height));
		shape.setPosition(x, y);
		if (outline) {
			shape.setOutlineThickness(outline_thickness);
			shape.setFillColor( sf::Color(0,0,0,0) );
			shape.setOutlineColor(color);
		}
		else {
			shape.setFillColor(color);
		}
		s_render_target->draw(shape);
	}

	void Object::drawLine(float x1, float y1, float x2, float y2, float thickness, sf::Color color) const {
		assert(s_render_target != nullptr && "drawLIne() can only be call from draw() method");
		// TODO:
	}
	void Object::drawCircle(float x, float y, float r, sf::Color color, bool outline, int outline_thickness) const {
		assert(s_render_target != nullptr && "drawCircle() can only be call from draw() method");
		sf::CircleShape circle(r);
		circle.setPosition(x - r, y - r);
		if (outline) {
			circle.setOutlineThickness(outline_thickness);
			circle.setFillColor( sf::Color(0,0,0,0) );
			circle.setOutlineColor(color);
		}
		else {
			circle.setFillColor(color);
		}
		s_render_target->draw(circle);
	}
	sf::RenderTarget& Object::getRenderTarget() const {
		assert(s_render_target != nullptr && "getRenderTarget() can only be call from draw() method");
		return *s_render_target;
	}

	void Object::emitSignal(Signal& signal) {
		signal.m_sender = this;
		assert(m_scene != nullptr);
		m_scene->addSignal(&signal);
	}
	
	Timer& Object::getTimer(const std::string& timer_name) {
		for (Timer* timer : m_timers) {
			if (timer->getName() == timer_name) return *timer;
		}
		assert( false && "invalid timer name to get" );
	}

	Animation& Object::getAnimation(const std::string& anim_name) {
		assert( m_animations.find(anim_name) != m_animations.end() && "invalid animation name to get" );
		return *(m_animations[anim_name]);
	}

	bool Object::hasAnimation(const std::string& anim_name) {
		return m_animations.find(anim_name) != m_animations.end();
	}

	bool Object::hasTimer(const std::string& timer_name) {
		for (Timer* timer : m_timers) {
			if (timer->getName() == timer_name) return true;
		}
		return false;
	}

	// setters
	void Object::setPosition(float x, float y) {
		sf::Transformable::setPosition(x, y);
		if (m_sprite) m_sprite->setPosition(getPosition());
		if (m_area) m_area->setPosition(getPosition());
	}
	void Object::setRotation(float angle) {
		sf::Transformable::setRotation(angle);
		if (m_sprite) m_sprite->setRotation(getRotation());
		if (m_area) m_area->setRotation(getRotation());
	}
	void Object::setScale(float scale_x, float scale_y) {
		sf::Transformable::setScale(scale_x, scale_y);
		if (m_sprite) m_sprite->setScale(getScale());
		if (m_area) m_area->setScale(getScale());
	}
	void Object::setOrigin(float x, float y) {
		sf::Transformable::setOrigin(x, y);
		if (m_sprite) m_sprite->setOrigin(x, y);
		if (m_area) m_area->setOrigin(x, y);
	}

	void Object::move(float x, float y) {
		setPosition(getPosition() + sf::Vector2f(x, y));
	}
	void Object::rotate(float angle) {
		setRotation(getRotation() + angle);
	}
	void Object::scale(float x, float y) {
		setScale(getScale().x * x, getScale().y * y);
	}

	void Object::setZIndex(int z_index) {
		m_z_index = z_index;
		if ( m_scene!= nullptr ) getScene().sortZIndex();
	}
	void Object::setSprite(Sprite* sprite) {
		m_sprite = sprite;
		m_sprite->setPosition(getPosition());
		m_sprite->setRotation(getRotation());
		m_sprite->setScale(getScale());
		m_sprite->setOrigin(getOrigin());
	}
	void Object::setArea(Area* area) { // if area == nullptr => area set as sprite rect. old area not deleted -> memory leak
		if (area == nullptr) {
			assert( m_sprite != nullptr && "without sprite can't call setArea(nullptr)" );
			assert( m_sprite->getLocalBounds().width > 0 && m_sprite->getLocalBounds().height > 0 && "without sprite.texture can't call setArea(nullptr)"  );
			
			auto rect = m_sprite->getLocalBounds();
			sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(rect.width, rect.height));
			auto area = Assets::newAsset<Area>();
			area->setShape(shape);
			setArea(area);
		}
		else {
			m_area = area;
			m_area->setPosition(getPosition());
			m_area->setRotation(getRotation());
			m_area->setScale(getScale());
			m_area->setOrigin(getOrigin());
		}
	}

	void Object::addAnimation(Animation* anim) {
		m_animations[ anim->getName() ] = anim;
		anim->setObject(this);
		// timer added to scene after calling init() in Application
	}
	
	void Object::addTimer(Timer* timer) {
		m_timers.push_back(timer);
		timer->m_signal.addReciever(this);
		// timer added to scene after calling init() in Application
	}

	void Object::clear() {
		m_timers.clear();
	}

}