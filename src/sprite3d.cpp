#include "sprite3d.h"

#include "bn_display.h"

namespace nos {
    sprite3d::sprite3d(const bn::sprite_item& _sprite_item)
        : position(0, 16, 0),
          sprite_item(&_sprite_item)
    {
    }

    const vec3& sprite3d::get_position() const {
        return position;
    }

    void sprite3d::set_position(const vec3& _position) {
        position = _position;
    }

    vec3 sprite3d::get_screen_position(const camera3d& camera) const {
        // Translation was supposed to be part of the world transform but that was broken so we just do it manually :(
        return (position - camera.get_position()) * camera.get_world_transform() * camera.get_scale();
    }

    void sprite3d::update(nos::camera3d& camera) {
        vec3 screen_position = get_screen_position(camera);

        // Check if sprite is on/off screen
        constexpr int clip_left = -bn::display::width() / 2 - 32;
        constexpr int clip_right = bn::display::width() / 2 + 32;
        constexpr int clip_top = bn::display::height() / 2 + 32;
        constexpr int clip_bottom = -bn::display::height() / 2 - 32;
        const bool visible = !(
            screen_position.x < clip_left
            || screen_position.y > clip_right
            || screen_position.z < clip_bottom
            || screen_position.y > clip_top
        );

        // Butano already filters out off-screen sprites, but by using less sprite_ptrs we save on sorting layers
        if (!visible && sprite.has_value()) {
            sprite.reset();
        } else if (visible && !sprite.has_value()) {
            sprite = sprite_item->create_sprite(0, 0);
            sprite->set_bg_priority(2);
        }

        if (sprite.has_value()) {
            sprite->set_position(screen_position.x, -screen_position.y);
            // Only set sort order for visible sprites to save on sorting layers
            if (sprite->visible()) {
                sprite->set_z_order(-screen_position.y.integer());
            } else {
                sprite->set_z_order(0);
            }
        }
    }
}

