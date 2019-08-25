#include "pch.h"
#include "XmlFile.h"

namespace pe
{
	XmlFile::XmlFile() {
		tinyxml2::XMLElement* assets = m_doc.NewElement("assets");
		m_doc.InsertFirstChild(assets);

		tinyxml2::XMLElement* textures = m_doc.NewElement("textures");
		tinyxml2::XMLElement* sprites = m_doc.NewElement("sprites");
		tinyxml2::XMLElement* backgrounds = m_doc.NewElement("backgrounds");
		tinyxml2::XMLElement* animations = m_doc.NewElement("animations");
		tinyxml2::XMLElement* areas = m_doc.NewElement("areas");

		m_doc.FirstChildElement()->InsertEndChild(textures);
		m_doc.FirstChildElement()->InsertEndChild(sprites);
		m_doc.FirstChildElement()->InsertEndChild(backgrounds);
		m_doc.FirstChildElement()->InsertEndChild(animations);
		m_doc.FirstChildElement()->InsertEndChild(areas);

		// test
		auto texr = m_doc.NewElement("texture");
		texr->SetAttribute("path","res/sheet.png");
		auto prop = m_doc.NewElement("property");
		prop->SetAttribute("smooth",false);
		prop->SetAttribute("repeat",true);
		texr->InsertEndChild(prop);
		textures->InsertEndChild(texr);


		auto spr = m_doc.NewElement("sprite");
		spr->SetAttribute( "name", "player" );
		auto tex = m_doc.NewElement("texture_path");
		tex->SetText("res/sheet.png");
		spr->InsertEndChild(tex);
		auto frames = m_doc.NewElement("frames");
		frames->SetAttribute("x",12);
		frames->SetAttribute("y",8);
		frames->SetAttribute("offset_x",0);
		frames->SetAttribute("offset_y",0);
		spr->InsertEndChild(frames);

		auto frame = m_doc.NewElement("frame");
		frame->SetAttribute("index",0);
		spr->InsertEndChild(frame);
		
		m_doc.FirstChildElement()->FirstChildElement()->NextSiblingElement()->InsertEndChild(spr);

		m_doc.SaveFile("assets.xml");
	}
}