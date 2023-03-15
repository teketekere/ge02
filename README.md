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

  cmake -GNinja -S. -Bbuild -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake .
  cmake --build build -j 12
  ```
