from conan import ConanFile
from conan.tools.cmake import cmake_layout

"""
Conan consumer recipe for ibis project
"""
class IbisConan(ConanFile):
    settings = 'os', 'arch', 'compiler', 'build_type'
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires('boost/1.78.0')
        self.requires('cli11/2.2.0')
        self.requires('fmt/8.1.1')
        self.requires('range-v3/0.11.0')

    def layout(self):
        cmake_layout(self)
