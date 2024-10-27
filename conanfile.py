from conan import ConanFile
from conan.tools.cmake import cmake_layout

"""
Conan consumer recipe for ibis project
"""
class IbisConan(ConanFile):
    settings = 'os', 'arch', 'compiler', 'build_type'
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires('boost/1.86.0')
        self.requires('cli11/2.4.2')
        self.requires('fmt/11.0.2')
        self.requires('range-v3/0.12.0')

    def layout(self):
        cmake_layout(self)
