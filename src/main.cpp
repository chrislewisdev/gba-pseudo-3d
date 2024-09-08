#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"
#include "bn_vector.h"
#include "bn_affine_bg_map_cell_info.h"

#include "sprite3d.h"
#include "camera3d.h"
#include "bg3d.h"
#include "wall3d.h"

#include "bn_sprite_items_fred_side_profile.h"
#include "bn_affine_bg_items_garden_floor.h"
#include "bn_affine_bg_items_garden_ceiling.h"

constexpr int metatile_size = 32;
constexpr int tile_size = 8;
constexpr int empty_tile = 0;

int get_tile(const bn::affine_bg_map_item& map, int x, int y) {
    int tx = x;
    int ty = y;

    auto cell = map.cell(tx, ty);
    bn::affine_bg_map_cell_info cell_info(cell);
    
    return cell_info.tile_index();
}

void generate_walls(const bn::affine_bg_map_item& map, bn::ivector<sp3d::wall3d>& storage) {
    const int map_width = map.dimensions().width();
    const int map_height = map.dimensions().height();
    const int half_width = (map_width * tile_size / 2);
    const int half_height = (map_height * tile_size / 2);

    for (int y = 0; y < map_height; y += 4) {
        for (int x = 0; x < map_width; x += 4) {
            int tile = get_tile(map, x, y);

            if (tile != empty_tile) {
                int left = x - 4 >= 0 ? get_tile(map, x - 4, y) : 0;
                int right = x + 4 < map_width ? get_tile(map, x + 4, y) : 0;
                int up = y - 4 >= 0 ? get_tile(map, x, y - 4) : 0;
                int down = y + 4 < map_height ? get_tile(map, x, y + 4) : 0;

                sp3d::vec3 wall_position(
                    x * tile_size + (metatile_size / 2) - half_width,
                    y * tile_size + (metatile_size / 2) - half_height,
                    metatile_size / 2
                );

                if (left == empty_tile) {
                    sp3d::vec3 offset(-metatile_size / 2, 0, 0);
                    storage.push_back(sp3d::wall3d(wall_position + offset, -sp3d::vec3::right));
                }
                if (right == empty_tile) {
                    sp3d::vec3 offset(metatile_size / 2, 0, 0);
                    storage.push_back(sp3d::wall3d(wall_position + offset, sp3d::vec3::right));
                }
                if (up == empty_tile) {
                    sp3d::vec3 offset(0, -metatile_size / 2, 0);
                    storage.push_back(sp3d::wall3d(wall_position + offset, -sp3d::vec3::forward));
                }
                if (down == empty_tile) {
                    sp3d::vec3 offset(0, metatile_size / 2, 0);
                    storage.push_back(sp3d::wall3d(wall_position + offset, sp3d::vec3::forward));
                }
            }
        }
    }
}

int main()
{
    bn::core::init();

    sp3d::camera3d camera;
    sp3d::sprite3d player(bn::sprite_items::fred_side_profile);
    sp3d::sprite3d npc(bn::sprite_items::fred_side_profile);
    sp3d::bg3d floor(bn::affine_bg_items::garden_floor);
    sp3d::bg3d ceiling(bn::affine_bg_items::garden_ceiling, 32, 1);
    bn::vector<sp3d::wall3d, 256> walls;
    generate_walls(bn::affine_bg_items::garden_ceiling.map_item(), walls);

    bool control_position = false;
    int heading = 0, pitch = 30;
    bn::fixed scale = 1;
    sp3d::vec3 camera_position;

    player.set_position(sp3d::vec3(0, 0, 16));
    npc.set_position(sp3d::vec3(50, 50, 16));

    while(true)
    {
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

        if (bn::keypad::a_held() && scale > bn::fixed(0.5)) {
            scale -= 0.1;
        } else if (bn::keypad::b_held() && scale < bn::fixed(1.5)) {
            scale += 0.1;
        }

        camera.update_camera(camera_position, pitch, heading, scale);
        player.update(camera);
        npc.update(camera);
        floor.update(camera);
        ceiling.update(camera);

        for (auto& wall : walls) {
            wall.update(camera);
        }

        bn::core::update();
    }
}
