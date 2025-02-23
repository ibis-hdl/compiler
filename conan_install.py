import subprocess
import platform
import argparse
from pathlib import Path

class ConanInstaller:
    def __init__(self):
        python_ver=tuple(map(int, platform.python_version_tuple()))
        # match statements are a feature of Python 3.10; take on
        # [[ENH] PEP 634 - Structural Pattern Matching #4029](
        # https://github.com/cython/cython/issues/4029)
        assert python_ver > (3,10,0), f"Python > 3.10 required, got {platform.python_version()}"

        match platform.system():
            case 'Linux':
                self.python = 'python3'
                self.shell = ['bash', '-c']
                self.generator = '"Ninja Multi-Config"'
                self.valid_profiles = ['gcc', 'clang', 'clang-libc++']
            case 'Windows':
                self.python = 'py'
                self.shell = ['pwsh', '-Command']
                self.generator = '"Ninja Multi-Config"'
                self.valid_profiles = ['msvc', 'msvc-cl']
            case 'Darwin':
                self.python = 'python3'
                self.shell = ['bash', '-c']
                self.generator = '"Ninja Multi-Config"'
                self.valid_profiles = ['clang', 'gcc']
            case 'FreeBSD':
                self.python = 'python3'
                self.shell = ['bash', '-c']
                self.generator = '"Ninja Multi-Config"'
                self.valid_profiles = ['clang-libc++']  
            case _:
                # https://docs.python.org/3/library/platform.html#platform.system
                raise Exception(f"Unsupported Platform {platform.system()}")
 
        # Set C++ standard to C++23, to avoid warning about modified CMAKE_CXX_STANDARD
        # value defined in conan_toolchain.cmake by ${workspaces}/compiler/CMakeLists.txt
        self.cppstd = 23
        self.supported_profiles = ['default', 'gcc', 'clang', 'clang-libc++', 'msvc', 'msvc-cl']
        self.supported_build_type = ['Release', 'Debug']

        parser = argparse.ArgumentParser(description='Conan install helper script.')
        parser.add_argument("--profile", default='default',
                            help=f"Conan profile used to install on {platform.system()}.",
                            type=str, choices=self.valid_profiles)
        parser.add_argument("--build-type", default=['Release'],
                            help="Space separated list of build types used to install.",
                            type=str, nargs='*', choices=self.supported_build_type)
        parser.add_argument('--dry', action='store_true')
        
        arg = parser.parse_args()

        self.conan_profile = arg.profile
        self.build_type = arg.build_type
        self.dry = arg.dry


    """
    Remove Conan generated CMake preset file.

    The generation of the e.g. 'ConanPresets.json', same as the 'CMakeUserPresets.json',
    is cumulative, it adds (include) new presets at every conan install. This may results
    into wrong includes and results into difficult to understand and irritating error
    messages. Hence, simply delete it before on each run.
    @see `conanfile.py` at generate().
    """
    def removeConanPresetsJson(self, file_name: str) -> None:
        file_path = Path(file_name)
        if file_path.exists():
            print(f"remove former generated Conan CMake preset '{file_name}'")
            Path(file_name).unlink(missing_ok=True)

    def do_install(self, build_type: str, conan_profile: str) -> None:

        if not build_type.lower() in [x.lower() for x in self.supported_build_type]:
            raise Exception(f"Unsupported CMAKE_BUILD_TYPE '{build_type}'")
        if not conan_profile.lower() in self.supported_profiles:
            raise Exception(f"Unsupported Conan profile '{conan_profile}'")

        cmd_args = [
            f"--settings compiler.cppstd={self.cppstd}",
            f"--settings build_type={build_type}",
            f"--conf tools.cmake.cmaketoolchain:generator={self.generator}",
            f"--build=missing",
            f"--profile:all={conan_profile}"
        ]
        cmd_line = f"conan install . " + f' '.join(cmd_args)

        try:
            print(f">>>  call `" + ' '.join([*self.shell, cmd_line]) + "`")
            if not self.dry:
                subprocess.run([*self.shell, cmd_line], check=True)
        except FileNotFoundError as e:
            print(f"Process failed because the executable could not be found.\n{e}")
        except subprocess.CalledProcessError as e:
            print(
                f"Process failed because did not return a successful return code. "
                f"Returned {e.returncode}\n{e}"
            )

    def install_config(self, build_type: list, conan_profile: str) -> None:
        for build_type in build_type:
            #print(f">>>  install {build_type} {conan_profile}")
            self.do_install(build_type, conan_profile)

    def install(self) -> None:
        self.install_config(self.build_type, self.conan_profile)

if __name__ == '__main__':
    conan = ConanInstaller()
    conan.removeConanPresetsJson('CMakeConanPresets.json')
    conan.install()
