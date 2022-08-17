# ToDo: [build profile (e.g: -pr:b=default)](
# https://docs.conan.io/en/latest/reference/profiles.html#build-profiles-and-host-profiles)

from conan import ConanFile
from conan.tools.cmake import CMakeDeps
from conan.tools.cmake import CMakeToolchain

"""
Conan consumer recipe for ibis project
"""
class IbisConan(ConanFile):
    settings = 'os', 'arch', 'compiler', 'build_type'
    requires = 'boost/1.78.0', \
        'cli11/2.2.0', \
        'fmt/8.1.1', \
        'range-v3/0.11.0'
    default_options = {
        # [Boost](https://conan.io/center/boost?tab=recipe)
        # override defaults to avoid unnecessary builds
        # Note: python is disabled due to NumPy dependency, see
        # [conan-center-index/issues/8826]{https://github.com/conan-io/conan-center-index/issues/8826}
        'boost:zstd': True,
        'boost:system_no_deprecated': True,
        'boost:asio_no_deprecated': True,
        'boost:filesystem_no_deprecated': True,
        'boost:diagnostic_definitions': False,
        'boost:without_python': True,
        'boost:without_context': True,
        'boost:without_contract': True,
        'boost:without_coroutine': True,
        'boost:without_fiber': True,
        'boost:without_graph': True,
        'boost:without_iostreams': True,
        'boost:without_log': True,
        'boost:without_math': True,
        'boost:without_nowide': True,
        'boost:without_program_options': True,
        'boost:without_random': True,
        'boost:without_regex': True,
        'boost:without_serialization': True,
        'boost:without_timer': True,
        'boost:without_type_erasure': True,
        'boost:without_wave': True,
        # [{fmt} lib](https://conan.io/center/fmt?tab=recipe)
        # deprecated API
        'fmt:with_fmt_alias' : False
    }

    """
    using the multi-configuration generator
    """
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        toolchain = CMakeToolchain(self)
        toolchain.generate()
