#include "CharacterSprite2D.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void CharacterSprite2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_iframes_alpha"), &CharacterSprite2D::get_iframes_alpha);
	ClassDB::bind_method(D_METHOD("set_iframes_alpha", "alpha"), &CharacterSprite2D::set_iframes_alpha);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "iframes_transparency", PROPERTY_HINT_RANGE, "0, 1, 0.01"),
		"set_iframes_alpha",
		"get_iframes_alpha");

	ClassDB::bind_method(D_METHOD("apply_transparency"), &CharacterSprite2D::apply_transparency);
	ClassDB::bind_method(D_METHOD("remove_transparency"), &CharacterSprite2D::remove_transparency);
}

CharacterSprite2D::CharacterSprite2D() {
	iframes_alpha = 0.5;
}

CharacterSprite2D::~CharacterSprite2D() {
	// destructor
}

void CharacterSprite2D::_ready() {
	Node* player = get_parent();
	if (player) {
		player->connect(
			"iframes_start",
			callable_mp(this, &CharacterSprite2D::_on_player_iframes_start)
		);

		player->connect(
			"iframes_stop",
			callable_mp(this, &CharacterSprite2D::_on_player_iframes_stop)
		);
	}
}

void CharacterSprite2D::_exit_tree() {
	Node* player = get_parent();

	if (player) {
		player->disconnect(
			"iframes_start",
			callable_mp(this, &CharacterSprite2D::_on_player_iframes_start)
		);

		player->disconnect(
			"iframes_stop",
			callable_mp(this, &CharacterSprite2D::_on_player_iframes_stop)
		);
	}
}


double CharacterSprite2D::get_iframes_alpha() {
	return iframes_alpha;
}

void CharacterSprite2D::set_iframes_alpha(double alpha) {
	iframes_alpha = alpha;
}

void CharacterSprite2D::apply_transparency() {
	set_modulate(Color(1, 1, 1, iframes_alpha));
}

void CharacterSprite2D::remove_transparency() {
	set_modulate(Color(1, 1, 1, 1));
}

void CharacterSprite2D::_on_player_iframes_start(Node* player) {
	apply_transparency();
}

void CharacterSprite2D::_on_player_iframes_stop(Node* player) {
	remove_transparency();
}