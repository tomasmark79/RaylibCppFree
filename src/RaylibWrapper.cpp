// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include <RaylibWrapper/RaylibWrapper.hpp>
#include <Assets/AssetContext.hpp>
#include <Logger/Logger.hpp>
#include <Utils/Utils.hpp>

#if defined(PLATFORM_WEB)
  #include <emscripten/emscripten.h>
#endif

#include <raylib.h>

namespace dotname {

  Texture2D texture;
  int virtualMain ();

  RaylibWrapper::RaylibWrapper () {
    LOG_D_STREAM << libName_ << " constructed ..." << std::endl;
    AssetContext::clearAssetsPath ();
  }

  RaylibWrapper::RaylibWrapper (const std::filesystem::path& assetsPath) : RaylibWrapper () {
    if (!assetsPath.empty ()) {
      AssetContext::setAssetsPath (assetsPath);
      LOG_D_STREAM << "Assets path given to the library\n"
                   << "╰➤ " << AssetContext::getAssetsPath () << std::endl;
      auto logo = std::ifstream (AssetContext::getAssetsPath () / "logo.png");

      virtualMain ();
    }
  }

  RaylibWrapper::~RaylibWrapper () {
    LOG_D_STREAM << libName_ << " ... destructed" << std::endl;
  }

  //----------------------------------------------------------------------------------
  // Global Variables Definition
  //----------------------------------------------------------------------------------
  int screenWidth = 800;
  int screenHeight = 450;

  //----------------------------------------------------------------------------------
  // Module Functions Declaration
  //----------------------------------------------------------------------------------
  void UpdateDrawFrame (void); // Update and Draw one frame

  //----------------------------------------------------------------------------------
  // Main Entry Point
  //----------------------------------------------------------------------------------
  int virtualMain () {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow (screenWidth, screenHeight, "raylib [core] example - basic window");
    texture = LoadTexture ((AssetContext::getAssetsPath () / "logo.png").string().c_str ());

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop (UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS (60); // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose ()) // Detect window close button or ESC key
    {
      UpdateDrawFrame ();
    }
#endif

    UnloadTexture (texture);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow (); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
  }

  //----------------------------------------------------------------------------------
  // Module Functions Definition
  //----------------------------------------------------------------------------------
  void UpdateDrawFrame (void) {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing ();

    ClearBackground (RAYWHITE);

    const int texture_x = screenWidth / 2 - texture.width / 2;
    const int texture_y = screenHeight / 2 - texture.height / 2;
    DrawTexture (texture, texture_x, texture_y, WHITE);

    const char* text = "Congrats! Your first window in DotName C++ Template!";
    const Vector2 text_size = MeasureTextEx (GetFontDefault (), text, 20, 1);
    DrawText (text, screenWidth / 2 - text_size.x / 2,
              texture_y + texture.height + text_size.y + 10, 20, BLACK);

    EndDrawing ();
    //----------------------------------------------------------------------------------
  }

} // namespace dotname