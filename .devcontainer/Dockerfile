FROM ubuntu:22.04
ARG CLANG_VERSION=13

RUN apt-get update -y && \
    # Utility
    apt-get install -y --no-install-recommends tzdata && \
    apt-get install -y --no-install-recommends apt-utils && \
    apt-get install -y --no-install-recommends \
    locales \
    nano \
    git && \
    # C++ build tools
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    gdb \
    ccache && \
    # Clang, LLVM
    apt-get install -y --no-install-recommends \
    lld-${CLANG_VERSION} \
    clangd-${CLANG_VERSION} \
    clang-${CLANG_VERSION} \
    clang-format-${CLANG_VERSION} \
    clang-tidy-${CLANG_VERSION} \
    llvm-${CLANG_VERSION} \
    llvm-${CLANG_VERSION}-dev \
    libclang-${CLANG_VERSION}-dev \
    libc++-${CLANG_VERSION}-dev \
    libc++abi-${CLANG_VERSION}-dev  && \
    # Python
    apt-get install -y --no-install-recommends \
    python3 \
    python3-dev \
    python3-pip \
    python3-wheel \
    python3-venv \
    python3-setuptools && \
    # Clean up
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /var/cache/apt/archives/*

# Locale
RUN echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen && \
    locale-gen

# Set compiler, linker, ... links
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-${CLANG_VERSION} 30 && \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-${CLANG_VERSION} 30 && \
    update-alternatives --install /usr/bin/clang clang /usr/bin/clang-${CLANG_VERSION} 30 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-${CLANG_VERSION} 30 && \
    update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-${CLANG_VERSION} 30 && \
    update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-${CLANG_VERSION} 30 && \
    update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-${CLANG_VERSION} 30 && \
    update-alternatives --install /usr/bin/ld ld /usr/bin/ld.lld-${CLANG_VERSION} 30 && \
    update-alternatives --install /usr/bin/ld ld /usr/bin/ld.gold 20 && \
    update-alternatives --install /usr/bin/ld ld /usr/bin/ld.bfd 10

# Install Python packages
RUN pip3 install conan

# libc++abi.aが/usr/lib/x86_64-linux-gnuに作られないため
# clangdでclangをコンパイラにした際stlの補完が効かない
RUN ln -s /usr/lib/llvm-${CLANG_VERSION}/lib/libc++abi.a /usr/lib/x86_64-linux-gnu/libc++abi.a && \
    ln -s /usr/lib/llvm-${CLANG_VERSION}/include/c++ /usr/local/include/c++
