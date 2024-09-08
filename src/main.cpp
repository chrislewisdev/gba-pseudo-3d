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

void generate_walls(const bn::affine_bg_map_item&, bn::ivector<sp3d::wall3d>&);

int main()
{
    bn::core::init();

    // Set up the scene
    sp3d::camera3d camera;
    sp3d::sprite3d player(bn::sprite_items::fred_side_profile);
    sp3d::sprite3d npc(bn::sprite_items::fred_side_profile);
    sp3d::bg3d floor(bn::affine_bg_items::garden_floor);
    sp3d::bg3d ceiling(bn::affine_bg_items::garden_ceiling, 32, 1);
    bn::vector<sp3d::wall3d, 256> walls;

    npc.set_position(sp3d::vec3(50, 50, 16));
    player.set_position(sp3d::vec3(0, 0, 16));
    generate_walls(bn::affine_bg_items::garden_ceiling.map_item(), walls);

    // For controlling the camera
    bool control_position = false;
    int heading = 0, pitch = 30;
    bn::fixed scale = 1.3;
    sp3d::vec3 camera_position;

    while(true)
    {
        if (bn::keypad::l_pressed()) {
            control_position = !control_position;
        }

        // Camera controls
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
            if (bn::keypad::up_held() && pitch > 20) {
                pitch -= 1;
            } else if (bn::keypad::down_held() && pitch < 85) {
                pitch += 1;
            }

            // Clamp heading angle to [0..360] range
            if (heading < 0) heading += 360;
            if (heading > 360) heading -= 360;
        }

        // Zoom controls. The more you zoom out, the more likely you are to run out of sprite sort layers
        // and to see walls disappearing from too many sprites showing on one scanline.
        if (bn::keypad::a_held() && scale > bn::fixed(0.8)) {
            scale -= 0.05;
        } else if (bn::keypad::b_held() && scale < bn::fixed(1.5)) {
            scale += 0.05;
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

int get_tile(const bn::affine_bg_map_item& map, int x, int y) {
    auto cell = map.cell(x, y);
    bn::affine_bg_map_cell_info cell_info(cell);
    return cell_info.tile_index();
}

/**
 * Wall generation will probably vary a lot depending on your game's level data and requirements.
 * This is a 'simple' implementation that scans through the ceiling tilemap and places walls wherever
 * it finds a ceiling edge. We assume that the ceiling is aligned to a 32x32 grid rather than 8x8,
 * so we only need to check every 4th tile.
 */
void generate_walls(const bn::affine_bg_map_item& map, bn::ivector<sp3d::wall3d>& storage) {
    const int map_width = map.dimensions().width();
    const int map_height = map.dimensions().height();
    const int half_width = (map_width * tile_size / 2);
    const int half_height = (map_height * tile_size / 2);

    for (int y = 0; y < map_height; y += 4) {
        for (int x = 0; x < map_width; x += 4) {
            int tile = get_tile(map, x, y);

            if (tile != empty_tile) {
                int left = x - 4 >= 0 ? get_tile(map, x - 4, y) : empty_tile;
                int right = x + 4 < map_width ? get_tile(map, x + 4, y) : empty_tile;
                int up = y - 4 >= 0 ? get_tile(map, x, y - 4) : empty_tile;
                int down = y + 4 < map_height ? get_tile(map, x, y + 4) : empty_tile;

                // Convert the co-ordinates from [0..512] to [-256..256], accounting for possible different tile/metatile sizes
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
