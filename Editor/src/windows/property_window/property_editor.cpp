#include "pch.h"
#include "proprty_editor.h"

// TEST
pe::Sprite* PropertyEditor::s_sprite;


void PropertyEditor::init() {}

void PropertyEditor::renderPropertyEditor()
{
	ImGui::Begin("properties");

	// test code
	static int h_frames = 1;
	static int v_frames = 1;
	static int v_offset = 0;
	static int h_offset = 0;
	static int frame    = 0;
	if (ImGui::InputInt("h frames", &h_frames)) {
		if (h_frames <= 1) h_frames = 1;
		s_sprite->setFrames(h_frames, v_frames, v_offset, h_offset);
	}
	if (ImGui::InputInt("v frames", &v_frames)) {
		if (v_frames <= 1) v_frames = 1;
		s_sprite->setFrames(h_frames, v_frames, v_offset, h_offset);
	}
	if (ImGui::InputInt("v offset", &v_offset)) {
		s_sprite->setFrames(h_frames, v_frames, v_offset, h_offset);
	}
	if (ImGui::InputInt("h offset", &h_offset)) {
		s_sprite->setFrames(h_frames, v_frames, v_offset, h_offset);
	}

	if (ImGui::InputInt("frame", &frame)) {
		if (frame <= 0) frame = 0;
		if (s_sprite->getFrameCount()-1 < frame) frame = s_sprite->getFrameCount()-1;
		s_sprite->setFrameIndex(frame);
	}
	
	ImGui::NewLine();

	static float h_scale = 1;
	static float  v_scale = 1;
	if (ImGui::InputFloat("h scale", &h_scale)) {
		if (h_scale <= 0) frame = 0;
		s_sprite->setScale(h_scale, v_scale);
	}
	if (ImGui::InputFloat("v scale", &v_scale)) {
		if (v_scale <= 0) frame = 0;
		s_sprite->setScale(h_scale, v_scale);
	}



	ImGui::End();
}