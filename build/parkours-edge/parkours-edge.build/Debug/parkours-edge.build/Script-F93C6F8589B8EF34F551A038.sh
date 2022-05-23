#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge
  /usr/local/Cellar/cmake/3.22.1/bin/cmake -E copy_directory /Users/dennis/Documents/projects/parkours-edge/parkours-edge/Assets /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge/Debug/Assets
  cd /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge
  /usr/local/Cellar/cmake/3.22.1/bin/cmake -E copy_directory /Users/dennis/Documents/projects/parkours-edge/parkours-edge/Shaders /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge/Debug/Shaders
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge
  /usr/local/Cellar/cmake/3.22.1/bin/cmake -E copy_directory /Users/dennis/Documents/projects/parkours-edge/parkours-edge/Assets /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge/Debug/Assets
  cd /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge
  /usr/local/Cellar/cmake/3.22.1/bin/cmake -E copy_directory /Users/dennis/Documents/projects/parkours-edge/parkours-edge/Shaders /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge/Debug/Shaders
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge
  /usr/local/Cellar/cmake/3.22.1/bin/cmake -E copy_directory /Users/dennis/Documents/projects/parkours-edge/parkours-edge/Assets /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge/Debug/Assets
  cd /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge
  /usr/local/Cellar/cmake/3.22.1/bin/cmake -E copy_directory /Users/dennis/Documents/projects/parkours-edge/parkours-edge/Shaders /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge/Debug/Shaders
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge
  /usr/local/Cellar/cmake/3.22.1/bin/cmake -E copy_directory /Users/dennis/Documents/projects/parkours-edge/parkours-edge/Assets /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge/Debug/Assets
  cd /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge
  /usr/local/Cellar/cmake/3.22.1/bin/cmake -E copy_directory /Users/dennis/Documents/projects/parkours-edge/parkours-edge/Shaders /Users/dennis/Documents/projects/parkours-edge/build/parkours-edge/Debug/Shaders
fi

