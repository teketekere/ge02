# ge02

## Features

- ECS (SparseSet + Archetype based)

## Env

- OS: Ubuntu22.04
- Compiler: Clang13

## Build

- Run [devcontainer](https://code.visualstudio.com/docs/devcontainers/create-dev-container)
- Execute following commands...

  ```shell
  pip3 install conan
  conan install -pr conan/linux_clang_13_Release  -pr:b conan/linux_clang_13_Release  --build missing --output-folder=build .

  cmake -S. -Bbuild -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake .
  cmake --build build -j 12

  # Debug build
  conan install -pr conan/linux_clang_13_Debug  -pr:b conan/linux_clang_13_Debug  --build missing --output-folder=build .

  # Debug with sanitizer
  conan install -pr conan/linux_clang_13_Debug  -pr:b conan/linux_clang_13_Debug -o sanitizer=True --build missing --output-folder=build .
  ```
