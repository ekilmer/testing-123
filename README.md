# Return Statement Highlighter Plugin for Binary Ninja

This Binary Ninja plugin provides visual highlighting of return statements across all IL (Intermediate Language) views. It helps analysts quickly identify function exit points and control flow patterns by highlighting return statements in a distinctive color.

This plugin was created as a working example for some CMake refactoring ideas I had in mind for Binary Ninja's public C++ API. Included in this repo is vcpkg packaging and handling of dependencies that only works with my [`cmake-refactor`](https://github.com/ekilmer/binaryninja-api/tree/cmake-refactor) branch. However, the CI for this plugin also tests upstream's compatible `dev` branch and when 5.0 is released, it will test against the stable commit.

## Features

- Highlights all return statements across different IL views
- Works in multiple IL representations:
  - Low Level IL (LLIL)
  - Medium Level IL (MLIL)
  - High Level IL (HLIL)
- Uses a semi-transparent blue highlight for easy visibility
- Integrates seamlessly with Binary Ninja's [RenderLayer](https://dev-api.binary.ninja/cpp/class_binary_ninja_1_1_render_layer.html) system

## Installation

### Prerequisites

- CMake 3.14 or newer
- C++17 compatible compiler
- Binary Ninja API
  - 4.3.6779-dev (Jan 31, 2025) or newer
    - Includes commit [8862696](https://github.com/Vector35/binaryninja-api/commit/8862696926173104957729683832591438161557)
  - Stable v5.0+ ([est. April 15, 2025 release](https://github.com/Vector35/binaryninja-api/milestone/23))

## Usage

1. Open a binary in Binary Ninja
2. In any IL view, click the hamburger menu button (top-right corner of the view)
3. Hover over "Render Layers"
4. Enable the "Highlight Return Statements" layer
5. All return statements will now be highlighted with a semi-transparent blue background

## How It Works

The plugin implements a custom `ReturnHighlightLayer` that:
1. Registers itself for all IL views during plugin initialization
2. Analyzes each line of disassembly/IL for return statements
3. Applies highlighting to lines containing return instructions
4. Uses Binary Ninja's [RenderLayer](https://dev-api.binary.ninja/cpp/class_binary_ninja_1_1_render_layer.html) API to integrate with the UI

The highlighting is implemented by checking keyword tokens for return-like text and applying a blue highlight with 50% opacity to matching lines.

## Improvements

- Allow the user to choose a color for line highlighting
- Insert fake "return" at end of function for void functions
  - Sometimes, Binary Ninja will use a do-while loop and the `while` is at the last expression in the function, which isn't highlighted
