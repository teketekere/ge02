from conan import ConanFile
from conan.tools.cmake import CMakeToolchain

class Lib(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"
    options = {"shared": [True, False], "fPIC": [True, False], "sanitizer": [True, False]}
    default_options = {"shared": False, "fPIC": True, "sanitizer": False}

    requires = "fmt/9.1.0"
    test_requires = "gtest/1.13.0"

    def generate(self):
        tc = CMakeToolchain(self)
        if self.options.sanitizer:
            tc.variables["GE_ENABLE_SAN"] = True
        tc.generate()
