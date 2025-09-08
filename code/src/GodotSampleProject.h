#pragma once

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {
	
	class GodotSampleProject : public Sprite2D {
		GDCLASS(GodotSampleProject, Sprite2D)

	private:
		double time_passed;

	protected:
		static void _bind_methods();

	public:
		GodotSampleProject();
		~GodotSampleProject();

		void _process(double delta) override;
	};

}

