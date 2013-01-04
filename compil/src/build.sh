#!/bin/bash

../compil-stable/tool/macosxx86/bin/generator --project-file=language/language.scompilprj -o ../../intermediate/test || exit 1
../boost/tool/macosxx86/bin/b2 toolset=darwin variant=debug link=static architecture=x86 address-model=64 -j1 --hash || exit 1