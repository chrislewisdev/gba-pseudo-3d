#include "bn_core.h"
#include "bn_sprite_ptr.h"

#include "o3d.h"
#include "camera3d.h"
#include "bg3d.h"

#include "bn_sprite_items_fred_side_profile.h"
#include "bn_affine_bg_items_garden_floor.h"
#include "bn_affine_bg_items_garden_ceiling.h"

int main()
{
    bn::core::init();

    nos::camera3d camera;
    nos::o3d player(bn::sprite_items::fred_side_profile);
    nos::o3d npc(bn::sprite_items::fred_side_profile);
    nos::bg3d floor(bn::affine_bg_items::garden_floor);
    nos::bg3d ceiling(bn::affine_bg_items::garden_ceiling, 32);
    int heading = 0;

    player.set_position(nos::vec3(0, 16, 0));
    npc.set_position(nos::vec3(50, 16, 50));

    bn::sprite_ptr sprite = bn::sprite_items::fred_side_profile.create_sprite(50, 50);

    while(true)
    {
        // if (++heading >= 360) heading = 0;

        camera.update_camera(nos::vec3::zero, 60, heading, 1);
        player.update(camera);
        npc.update(camera);
        floor.update(camera);
        ceiling.update(camera);
        bn::core::update();
    }
}
