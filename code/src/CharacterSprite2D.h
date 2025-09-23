#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/timer.hpp>

namespace godot {
	class CharacterSprite2D : public Sprite2D {
		GDCLASS(CharacterSprite2D, Sprite2D)

	private:
		double iframes_alpha;
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

		Color get_hit_color();
		void set_hit_color(Color p_hit_color);

		void apply_transparency();
		void remove_transparency();
	};
}