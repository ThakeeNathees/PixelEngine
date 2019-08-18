#include "pch.h"
#include "..//Scene.h" // for referencing scene of the object; scene has objects included

namespace pe
{
	// static initialization
	int Object::s_object_count = 0;
	sf::RenderTarget* Object::s_render_target = nullptr;
	sf::Color Object::m_default_color = sf::Color(50, 75, 100, 255);

	Object::Object() {
		m_id = ++s_object_count;
		m_dbg_origin = new sf::CircleShape(3);
		m_dbg_origin->setFillColor( sf::Color(150, 75, 150, 200) );
	}
	Object::~Object() {
		if (m_sprite)		delete m_sprite;
		if (m_dbg_origin)	delete m_dbg_origin;
	}
	

	// virtual function
	void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		s_render_target = &target; // TODO: multiple viwe case
		draw();
		drawDebug(target);
		s_render_target = nullptr;
	}
	void Object::draw() const {
		drawSelf();
	}
	void Object::drawDebug(sf::RenderTarget& target) const {
		if (m_scene != nullptr && m_scene->isDebugMode() ) {
			if (m_area != nullptr) target.draw(  m_area->getShape()  );
			if (m_dbg_origin) {
				m_dbg_origin->setPosition( getPosition() );
				target.draw( *m_dbg_origin );
			}
		}
	}
	void Object::draw(const sf::Drawable& drawable) const {
		assert( s_render_target != nullptr && "draw(const sf::Drawable&) can only be call from draw() method" );
		s_render_target->draw(drawable);

	}

	void Object::drawSelf() const {
		assert( s_render_target != nullptr && "drawself() can only be call from draw() method" );
		if (hasSprite()) s_render_target->draw(getSprite());
	}

	void Object::drawRectangle(float x, float y, float width, float height, sf::Color color) const { // TODO: outline only, outline thickness ...
		assert( s_render_target != nullptr && "drawRectangle() can only be call from draw() method" );
		sf::RectangleShape shape(sf::Vector2f( width, height ));
		shape.setPosition(x, y);
		shape.setFillColor(color);
		s_render_target->draw( shape );
	}

	void Object::drawLine(float x1, float y1, float x2, float y2, float thickness, sf::Color color) const {
		assert( s_render_target != nullptr && "drawLIne() can only be call from draw() method" );
		// TODO:
	}
	void Object::drawCircle(float x, float y, float r, sf::Color color) const {
		assert( s_render_target != nullptr && "drawCircle() can only be call from draw() method" );
		sf::CircleShape circle(r);
		circle.setPosition( x-r, y-r );
		circle.setFillColor( color );
		s_render_target->draw( circle );
	}
	sf::RenderTarget& Object::getRenderTarget() const {
		assert( s_render_target != nullptr && "getRenderTarget() can only be call from draw() method" );
		return *s_render_target;
	}

	void Object::emitSignal(Signal& signal) {
		signal.m_sender = this;
		assert(  m_scene != nullptr );
		m_scene->addSignals(&signal);
	}

	// setters
	void Object::setPosition(float x, float y) {
		sf::Transformable::setPosition(x, y);
		if (m_sprite) m_sprite->setPosition( getPosition() );
		if (m_area) m_area->setPosition( getPosition() );
	}
	void Object::setRotation(float angle) {
		sf::Transformable::setRotation(angle);
		if (m_sprite) m_sprite->setRotation( getRotation() );
		if (m_area) m_area->setRotation( getRotation() );
	}
	void Object::setScale(float x, float y) {
		sf::Transformable::setScale(x, y);
		if (m_sprite) m_sprite->setScale(getScale());
		if (m_area) m_area->setScale(getScale());
	}
	void Object::setOrigin(float x, float y) {
		sf::Transformable::setOrigin(x, y);
		if (m_sprite) m_sprite->setOrigin( x, y );
		if (m_area) m_area->setOrigin( x, y );
	}

	void Object::move(float x, float y) {
		setPosition( getPosition() + sf::Vector2f(x, y) );
	}
	void Object::rotate(float angle) {
		setRotation( getRotation() + angle );
	}
	void Object::scale(float x, float y) {
		setScale(  getScale().x * x, getScale().y * y  );
	}

	void Object::setZIndex(int z_index) {
		m_z_index = z_index;
		// TODO: signal call Scene.sortObjectZIndex() 
	}
	void Object::setSprite(Sprite* sprite) {
		m_sprite = sprite;
		m_sprite->setPosition(getPosition());
		m_sprite->setRotation(getRotation());
		m_sprite->setScale(getScale());
	}
	void Object::setArea(Area* area) { // if area == nullptr -> area set as sprite rect.
		if (area == nullptr && m_sprite != nullptr ) {
			if (m_area) delete m_area;
			auto rect = m_sprite->getLocalBounds();
			sf::RectangleShape* shape = new sf::RectangleShape( sf::Vector2f(rect.width, rect.height) );
			auto area = new Area();
			area->setShape( shape );
			setArea( area );
		}
		else {
			m_area = area;
			m_area->setPosition(getPosition());
			m_area->setRotation(getRotation());
			m_area->setScale(getScale());
		}
	}

}