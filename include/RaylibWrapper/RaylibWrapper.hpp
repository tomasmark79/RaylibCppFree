// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#ifndef __RAYLIBWRAPPER_HPP
#define __RAYLIBWRAPPER_HPP

#include <RaylibWrapper/version.h>
#include <filesystem>
#include <string>

// Public API

namespace dotname {

  class RaylibWrapper {

    const std::string libName_ = std::string ("RaylibWrapper v.") + RAYLIBWRAPPER_VERSION;

  public:
    RaylibWrapper ();
    RaylibWrapper (const std::filesystem::path& assetsPath);
    ~RaylibWrapper ();
  };

} // namespace dotname

#endif // __RAYLIBWRAPPER_HPP