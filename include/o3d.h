#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_animate_actions.h"
#include "bn_string_view.h"
#include "bn_fixed_rect.h"

#include "vec3.h"
#include "camera3d.h"

namespace nos {
    class o3d {
        protected:
            vec3 position;
            bn::optional<bn::sprite_ptr> sprite;
            const bn::sprite_item* sprite_item;

        public:
            o3d(const bn::sprite_item& _sprite_item);
            virtual ~o3d() = default;

            const vec3& get_position() const;
            void set_position(const vec3& _position);
            vec3 get_screen_position(const camera3d& camera) const;

            virtual void update(nos::camera3d& camera);
    };
}

