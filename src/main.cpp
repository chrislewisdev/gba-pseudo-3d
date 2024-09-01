#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"

#include "sprite3d.h"
#include "camera3d.h"
#include "bg3d.h"

#include "bn_sprite_items_fred_side_profile.h"
#include "bn_affine_bg_items_garden_floor.h"
#include "bn_affine_bg_items_garden_ceiling.h"

int main()
{
    bn::core::init();

    nos::camera3d camera;
    nos::sprite3d player(bn::sprite_items::fred_side_profile);
    nos::sprite3d npc(bn::sprite_items::fred_side_profile);
    nos::bg3d floor(bn::affine_bg_items::garden_floor);
    nos::bg3d ceiling(bn::affine_bg_items::garden_ceiling, 32);

    bool control_position = false;
    int heading = 0, pitch = 30;
    nos::vec3 camera_position;

    player.set_position(nos::vec3(0, 0, 16));
    npc.set_position(nos::vec3(50, 50, 16));

    // bn::sprite_ptr sprite = bn::sprite_items::fred_side_profile.create_sprite(50, 50);

    while(true)
    {
        // if (++heading >= 360) heading = 0;

        if (bn::keypad::l_pressed()) {
            control_position = !control_position;
        }

        if (control_position) {
            if (bn::keypad::left_held()) {
                camera_position.x -= 1;
            } else if (bn::keypad::right_held()) {
                camera_position.x += 1;
            }
            if (bn::keypad::up_held() && pitch > 0) {
                camera_position.y -= 1;
            } else if (bn::keypad::down_held() && pitch < 85) {
                camera_position.y += 1;
            }
        } else {
            if (bn::keypad::left_held()) {
                heading += 1;
            } else if (bn::keypad::right_held()) {
                heading -= 1;
            }
            if (bn::keypad::up_held() && pitch > 0) {
                pitch -= 1;
            } else if (bn::keypad::down_held() && pitch < 85) {
                pitch += 1;
            }

            // Clamp heading angle to [0..360] range
            if (heading < 0) heading += 360;
            if (heading > 360) heading -= 360;
        }

        camera.update_camera(camera_position, pitch, heading, 1);
        player.update(camera);
        npc.update(camera);
        floor.update(camera);
        ceiling.update(camera);
        bn::core::update();
    }
}
