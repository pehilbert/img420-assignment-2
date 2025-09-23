#include "CharacterSprite2D.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/property_tweener.hpp>

using namespace godot;

void CharacterSprite2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_iframes_alpha"), &CharacterSprite2D::get_iframes_alpha);
	ClassDB::bind_method(D_METHOD("set_iframes_alpha", "alpha"), &CharacterSprite2D::set_iframes_alpha);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "iframes_transparency", PROPERTY_HINT_RANGE, "0, 1, 0.01"),
		"set_iframes_alpha",
		"get_iframes_alpha");

	ClassDB::bind_method(D_METHOD("get_death_anim_duration"), &CharacterSprite2D::get_death_anim_duration);
	ClassDB::bind_method(D_METHOD("set_death_anim_duration", "duration"), &CharacterSprite2D::set_death_anim_duration);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "death_animation_duration"),
		"set_death_anim_duration",
		"get_death_anim_duration");

	ClassDB::bind_method(D_METHOD("apply_transparency"), &CharacterSprite2D::apply_transparency);
	ClassDB::bind_method(D_METHOD("remove_transparency"), &CharacterSprite2D::remove_transparency);

	ADD_SIGNAL(MethodInfo("death_animation_finished", PropertyInfo(Variant::OBJECT, "player")));
}

CharacterSprite2D::CharacterSprite2D() {
	iframes_alpha = 0.5;
	death_animation_duration = 1;
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
		
		player->connect(
			"death",
			callable_mp(this, &CharacterSprite2D::death_animation)
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

		player->disconnect(
			"death",
			callable_mp(this, &CharacterSprite2D::death_animation)
		);
	}
}


double CharacterSprite2D::get_iframes_alpha() {
	return iframes_alpha;
}

void CharacterSprite2D::set_iframes_alpha(double alpha) {
	iframes_alpha = alpha;
}

double CharacterSprite2D::get_death_anim_duration() {
	return death_animation_duration;
}

void CharacterSprite2D::set_death_anim_duration(double duration) {
	death_animation_duration = duration;
}

void CharacterSprite2D::apply_transparency() {
	set_modulate(Color(1, 1, 1, iframes_alpha));
}

void CharacterSprite2D::remove_transparency() {
	set_modulate(Color(1, 1, 1, 1));
}

void CharacterSprite2D::death_animation(Node* player) {
	// optional: stop other logic while dying
	set_process(false);
	set_physics_process(false);

	Ref<Tween> t = get_tree()->create_tween();
	t->tween_property(this, "modulate:a", 0.0, death_animation_duration);
	t->connect("finished", callable_mp(this, &CharacterSprite2D::_on_death_tween_finished));
}

void CharacterSprite2D::_on_death_tween_finished() {
	emit_signal("death_animation_finished", get_parent());
	queue_free();
}

void CharacterSprite2D::_on_player_iframes_start(Node* player) {
	apply_transparency();
}

void CharacterSprite2D::_on_player_iframes_stop(Node* player) {
	remove_transparency();
}