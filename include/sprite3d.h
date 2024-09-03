#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"

#include "vec3.h"
#include "camera3d.h"

namespace sp3d {
    class sprite3d {
        protected:
            vec3 position;
            bn::optional<bn::sprite_ptr> sprite;
            const bn::sprite_item* sprite_item;

        public:
            sprite3d(const bn::sprite_item& _sprite_item);
            virtual ~sprite3d() = default;

            const vec3& get_position() const;
            void set_position(const vec3& _position);

            virtual void update(sp3d::camera3d& camera);
    };
}

