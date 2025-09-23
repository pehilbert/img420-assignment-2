#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/timer.hpp>

// Implements i-frames and death animations for a Player node
namespace godot {
	class CharacterSprite2D : public Sprite2D {
		GDCLASS(CharacterSprite2D, Sprite2D)

	private:
		double iframes_alpha;
		double death_animation_duration;

		void death_animation(Node* player);
		void _on_death_tween_finished();

		void _on_player_iframes_start(Node* player);
		void _on_player_iframes_stop(Node* player);

	protected:
		static void _bind_methods();

	public:
		CharacterSprite2D();
		~CharacterSprite2D();

		void _ready() override;
		void _exit_tree() override;

		double get_iframes_alpha();
		void set_iframes_alpha(double alpha);

		double get_death_anim_duration();
		void set_death_anim_duration(double duration);

		void apply_transparency();
		void remove_transparency();
	};
}