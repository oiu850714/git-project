from conans import ConanFile, CMake

class ConanPackage(ConanFile):
    name = 'libgit-practice'
    version = '0.1.0'

    generators = 'cmake_find_package'

    requires = [
        ('libgit2/1.1.0')
    ]
