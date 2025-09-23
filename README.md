# Platformer Game Extended
This GDExtension and example platformer project adds a new node, CharacterSprite2D, which extends Node2D and adds character animations for i-frames, where it turns transparent, and a death animation which makes the sprite fade out and then destroy itself.

The i-frames animation responds to the iframes start and stop signals from the player node, applying or removing the transparency effect. The death animation triggers upon receiving the death signal from the player node, emits a signal upon its completion, which causes the death screen to appear.
