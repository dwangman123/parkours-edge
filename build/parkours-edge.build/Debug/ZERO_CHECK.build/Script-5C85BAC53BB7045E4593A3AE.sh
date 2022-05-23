#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/dennis/Documents/projects/parkours-edge/build
  make -f /Users/dennis/Documents/projects/parkours-edge/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/dennis/Documents/projects/parkours-edge/build
  make -f /Users/dennis/Documents/projects/parkours-edge/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/dennis/Documents/projects/parkours-edge/build
  make -f /Users/dennis/Documents/projects/parkours-edge/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/dennis/Documents/projects/parkours-edge/build
  make -f /Users/dennis/Documents/projects/parkours-edge/build/CMakeScripts/ReRunCMake.make
fi

