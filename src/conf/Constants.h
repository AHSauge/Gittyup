//
//          Copyright (c) 2026
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Alf Henrik Sauge
//
// This file contains application wide constants

#include <cstdint>

/// @brief Number of bytes to read to determine if a file is binary or not
const std::size_t kMaxReadBinary = 64 * 1024;

/// @brief New (untracked) files larger than this are not rendered
/// automatically, since the whole file is shown as the "diff". The user has
/// to explicitly request to load them via the "Load Diff" button.
const std::size_t kMaxAutoLoadDiffSize = 1024 * 1024; // 1 MB

/// @brief Diffs that touch more than this many lines (additions + deletions)
/// are not rendered automatically, regardless of the file's total size. A
/// small change in a huge file is still loaded automatically; only the diff
/// itself has to stay small. The user has to explicitly request to load
/// larger diffs via the "Load Diff" button.
const std::size_t kMaxAutoLoadDiffLines = 10000;
