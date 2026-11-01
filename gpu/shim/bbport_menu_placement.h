// SPDX-License-Identifier: GPL-2.0-or-later
// bbport: where the settings menu goes on screen (chosen by the overlay, checked by a test).
#pragma once

#include <algorithm>

namespace BbOverlay {

/// The settings menu's frame: top-left corner, width, and the tallest height that fits on screen.
struct MenuFrame {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
};

/// Places the menu in the screen's work area: at the place it was moved to (menu_x/menu_y are
/// fractions of the work area; negative values mean the default top-left), kept on screen, and
/// lifted when too little of it would be visible. The height is the room left below that place,
/// which is what keeps the menu usable: its content is taller than 1080p, and a window that grew
/// past the bottom edge left its last rows (Close, Quit) below the screen, out of reach even at
/// the end of the scroll.
inline MenuFrame PlaceMenu(float area_x, float area_y, float area_w, float area_h, float menu_x,
                           float menu_y, float scale) {
    MenuFrame frame{.x = area_x + 40.0f * scale,
                    .y = area_y + 40.0f * scale,
                    .width = 620.0f * scale,
                    .height = 0.0f};
    if (menu_x >= 0.0f && menu_y >= 0.0f) {
        const float margin = 80.0f * scale;
        frame.x = area_x + std::clamp(menu_x * area_w, 0.0f, std::max(area_w - margin, 0.0f));
        frame.y = area_y + std::clamp(menu_y * area_h, 0.0f, std::max(area_h - margin, 0.0f));
    }
    const float gap = 8.0f * scale;
    const float min_height = std::min(420.0f * scale, area_h * 0.6f);
    frame.height = area_h - (frame.y - area_y) - gap;
    if (frame.height < min_height) {
        frame.y = area_y + std::max(area_h - min_height - gap, gap);
        frame.height = area_h - (frame.y - area_y) - gap;
    }
    return frame;
}

} // namespace BbOverlay
