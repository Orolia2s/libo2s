import os
from conan import ConanFile
from conan.tools.gnu import Autotools
from conan.tools.scm import Git
from conan.tools.files import save, load

class LibO2sConan(ConanFile):
    name = 'libo2s'
    author = 'A. Gagniere <antoine.gagniere@orolia2s.com>'
    url = 'https://gitlab.orolia2s.com/orolia2s/libo2s.git'
    license = 'proprietary'
    description = 'Fundamental datastructures for C'
    topics = ('datastructures')

    settings = ('os', 'arch', 'compiler', 'build_type')
    options = {
        'shared': [True, False],
        'fPIC': [True, False]
    }
    default_options = {
        'shared': False,
        'fPIC': True
    }

    generators = 'AutotoolsToolchain'
    exports_sources = 'Makefile', 'src/*.[ch]', 'include/*.h', 'README.md'

    def export(self):
        # Only files that are necessary for the evaluation of the conanfile.py
        # recipe must be exported with this method. Files necessary for
        # building from sources should be exported with the exports_sources
        # attribute or the export_source() method.
        git = Git(self, folder=self.recipe_folder)
        version = git.run('tag --sort "-version:refname" --merged').split('\n', 1)[0]
        save(self, os.path.join(self.export_folder, 'version.txt'), version)

    def set_version(self):
        self.version = load(self, 'version.txt')

    def configure(self):
        self.settings.rm_safe('compiler.libcxx')
        self.settings.rm_safe('compiler.cppstd')
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def build(self):
        autotools = Autotools(self)
        autotools.make('shared' if self.options.shared else 'static')
        autotools.make('clean')

    def package(self):
        self.copy('*.h',  dst='include', src='include')
        self.copy('*.a',  dst='lib', keep_path=False)
        self.copy('*.so', dst='lib', keep_path=False)
        self.copy('README.md')

    def package_info(self):
        self.cpp_info.libs = ['o2s']
