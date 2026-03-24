# Test Maps for BalatroisD Parser

This directory contains comprehensive test cases to validate the .cub file parser.

## Valid Test Cases

| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | valid_minimal.cub | Minimal valid map configuration | ✅ | |
| 2 | valid_with_spaces.cub | Basic map with spaces inside | ✅ | |
| 3 | valid_spaces_in_map.cub | Complex map with spaces | | | invalid_test
| 4 | valid_player_north.cub | Player facing North | ✅ | |
| 5 | valid_player_south.cub | Player facing South | ✅ | |
| 6 | valid_player_east.cub | Player facing East | ✅ | |
| 7 | valid_player_west.cub | Player facing West | ✅ | |
| 8 | valid_irregular_shape.cub | Irregular map shape with indentation | ✅ | |
| 9 | valid_large_map.cub | Large rectangular map | ✅ | |
| 10 | valid_multiple_empty_lines.cub | Multiple empty lines between elements | ✅ | |
| 11 | valid_random_order.cub | Elements in random order | ❌ | |
| 12 | valid_extra_spaces.cub | Extra spaces in element definitions | ✅ | |
| 13 | valid_complex_layout.cub | Complex multi-section layout | ✅ | |
| 14 | valid_tiny.cub | Smallest possible valid map (3x3) | ✅ | |
| 15 | valid_corner_player.cub | Player in corner position | ✅ | |
| 16 | valid_only_walls_and_player.cub | Map with only walls surrounding player | ✅ | |
| 17 | valid_maze_like.cub | Maze-like structure | ✅ | |
| 18 | valid_l_shaped.cub | L-shaped map layout | ✅ | |
| 19 | valid_rectangular.cub | Wide rectangular map | ✅ | |
| 20 | valid_max_rgb.cub | Maximum RGB values (255,255,255) | ✅ | |
| 21 | valid_square.cub | Perfect square map | ✅ | |

**Status Legend:** ⬜ Not Tested | ✅ Pass | ❌ Fail

---

## Invalid Test Cases - Map Structure

| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | invalid_open_top.cub | Map not closed at top | ✅ | | 
| 2 | invalid_open_bottom.cub | Map not closed at bottom | ✅ |  |
| 3 | invalid_open_left.cub | Map not closed on left side | ✅ | |
| 4 | invalid_open_right.cub | Map not closed on right side | ✅ | |
| 5 | invalid_space_hole.cub | Space creating a hole in walls | ✅ | |
| 6 | invalid_space_outside_wall.cub | Space touching outside of map | ⬜ | existe pas |
| 7 | invalid_uneven_lines.cub | Lines of different lengths creating holes | ⬜ | existe pas |
| 8 | invalid_player_in_space.cub | Player surrounded by spaces (not enclosed) | ✅ | |
| 9 | invalid_adjacent_spaces.cub | Multiple spaces not properly enclosed | ✅ | |

## Invalid Test Cases - Player

| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | invalid_no_player.cub | No player position defined | ✅ | |
| 2 | invalid_multiple_players.cub | Multiple player positions | ✅ | |
| 3 | invalid_player_on_edge.cub | Player on edge (not surrounded by walls/floor) | ✅ | |
| 4 | invalid_lowercase_player.cub | Player character in lowercase | ✅ | |

## Invalid Test Cases - Characters

| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | invalid_character_in_map.cub | Invalid character (X) in map | ✅ | |
| 2 | invalid_tab_character.cub | Tab character instead of space | ✅ | |

## Invalid Test Cases - Required Elements

| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | invalid_missing_north_texture.cub | Missing NO texture | ✅ | |
| 2 | invalid_missing_south_texture.cub | Missing SO texture | ✅ | |
| 3 | invalid_missing_floor_color.cub | Missing F color | ✅ | |
| 4 | invalid_missing_ceiling_color.cub | Missing C color | ✅ | |
| 5 | invalid_only_map.cub | Map without any configuration | ✅ | |
| 6 | invalid_empty_map.cub | Configuration without map | ✅ | |

## Invalid Test Cases - Colors

| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | invalid_color_out_of_range.cub | RGB value > 255 | ✅ | |
| 2 | invalid_color_negative.cub | Negative RGB value | ✅ | |
| 3 | invalid_color_format.cub | Wrong number of RGB components | ✅ | |
| 4 | invalid_color_extra_comma.cub | Extra comma in color | ❌ | |
| 5 | invalid_color_letters.cub | Letters in RGB values | ✅ | |

## Invalid Test Cases - Duplicates & Order

| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | invalid_duplicate_north.cub | Duplicate NO texture definition | ✅ | |
| 2 | invalid_map_not_last.cub | Map not at the end of file | ✅ | |

## Invalid Test Cases - Map Continuity

| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | invalid_newline_in_map.cub | Empty line within map | ❎ | Se lance en ignorant la new line |

## Invalid Test Cases - File Extension

| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | invalid_wrong_extension.cu | Wrong file extension (.cu instead of .cub) | ⬜ | |

## Testing Recommendations

### Parser Should Accept:
- All files prefixed with `valid_`
- Maps with irregular shapes (L-shaped, indented)
- Multiple empty lines between configuration elements
- Extra spaces in element definitions
- Elements in any order (except map must be last)
- Spaces as valid map characters (when properly enclosed)

### Parser Should Reject:
- All files prefixed with `invalid_`
- Maps not surrounded by walls
- Multiple or missing players
- Invalid characters in map
- Missing required elements (NO, SO, WE, EA, F, C)
- RGB values outside 0-255 range
- Map not being the last element
- Empty lines within the map

---

## How to Use This Test Suite

### Testing Individual Files
```bash
./BalatroisD test_maps/valid_minimal.cub
./BalatroisD test_maps/invalid_open_top.cub
```

### Recording Results
1. After testing each file, update the **Status** column:
   - Replace ⬜ with ⬜ if the test passed (behaved as expected)
   - Replace ⬜ with ❌ if the test failed (unexpected behavior)

2. In the **Notes** column, write:
   - For **valid** tests that fail: what error was thrown
   - For **invalid** tests that pass: note that it was incorrectly accepted
   - For **invalid** tests that fail: optionally note the error message
   - Any other observations or issues

### Example
| # | File | Description | Status | Notes |
|---|------|-------------|--------|-------|
| 1 | valid_minimal.cub | Minimal valid map configuration | ⬜ | Works correctly |
| 2 | invalid_open_top.cub | Map not closed at top | ❌ | Parser didn't detect open wall, game loaded |
