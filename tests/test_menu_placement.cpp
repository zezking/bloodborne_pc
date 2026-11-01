// SPDX-License-Identifier: GPL-2.0-or-later
#include <cassert>
#include <cstdio>
#include "gpu/shim/bbport_menu_placement.h"

int main() {
    using namespace BbOverlay;
    // 1080p: the menu's content is taller than the screen. Its height stops at the room below its
    // place, so its last row (Close, Quit) stays on screen at the end of the scroll.
    const MenuFrame full_hd = PlaceMenu(0, 0, 1920, 1080, -1.0f, -1.0f, 1.0f);
    assert(full_hd.x == 40.0f && full_hd.y == 40.0f);
    assert(full_hd.width == 620.0f);
    assert(full_hd.height == 1032.0f); // 1080 - 40 - 8
    assert(full_hd.y + full_hd.height <= 1080.0f);

    // 4K (scale 2): everything follows the display height.
    const MenuFrame uhd = PlaceMenu(0, 0, 3840, 2160, -1.0f, -1.0f, 2.0f);
    assert(uhd.x == 80.0f && uhd.y == 80.0f && uhd.width == 1240.0f);
    assert(uhd.height == 2064.0f); // 2160 - 80 - 16
    assert(uhd.y + uhd.height <= 2160.0f);

    // Remembered at the bottom edge: lifted so a useful part fits, still on screen.
    const MenuFrame low = PlaceMenu(0, 0, 1920, 1080, 0.0f, 1.0f, 1.0f);
    assert(low.height >= 420.0f); // min(420, 60% of the height)
    assert(low.y + low.height <= 1080.0f);

    // Remembered at the right edge: kept horizontally on screen.
    const MenuFrame right = PlaceMenu(0, 0, 1920, 1080, 1.0f, 0.0f, 1.0f);
    assert(right.x <= 1920.0f - 80.0f);

    // A work area that starts lower (a panel): the room is measured from the area's own bottom.
    const MenuFrame offset = PlaceMenu(0, 100, 1920, 980, -1.0f, -1.0f, 1.0f);
    assert(offset.y == 140.0f);
    assert(offset.y + offset.height <= 1080.0f);

    std::puts("Menu placement: PASS (1080p, 4K, remembered edges, offset work area)");
}
