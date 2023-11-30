import os
from conan import ConanFile
from conan.tools.gnu import Autotools, AutotoolsToolchain, AutotoolsDeps
from conan.tools.scm import Git
from conan.tools.files import save, load, copy

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

    exports_sources = 'Makefile', 'src/*.[ch]', 'include/*.h', 'README.md'

    def export(self):
        git = Git(self, folder=self.recipe_folder)
        version = git.run('tag --sort "-version:refname" --merged').split('\n', 1)[0]
        save(self, os.path.join(self.export_folder, 'version.txt'), version)

    def set_version(self):
        try:
            self.version = load(self, 'version.txt').strip()
        except:
            git = Git(self, folder=self.recipe_folder)
            self.version = git.run('tag --sort "-version:refname" --merged').split('\n', 1)[0]

    def configure(self):
        self.settings.rm_safe('compiler.libcxx')
        self.settings.rm_safe('compiler.cppstd')
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def generate(self):
        autotools = AutotoolsDeps(self)
        autotools.environment.define('Version', self.version)
        autotools.generate()
        AutotoolsToolchain(self).generate()

    def build(self):
        autotools = Autotools(self)
        autotools.make('shared' if self.options.shared else 'static')
        autotools.make('clean')

    def package(self):
        copy(self, '*.h',
             os.path.join(self.source_folder, 'include'),
             os.path.join(self.package_folder, 'include'))
        copy(self, '*.a', self.build_folder,
             os.path.join(self.package_folder, 'lib'))
        copy(self, '*.so', self.build_folder,
             os.path.join(self.package_folder, 'lib'))
        copy(self, 'version.txt', self.source_folder, self.package_folder)
        copy(self, 'README.md', self.source_folder, self.package_folder)

    def package_info(self):
        self.cpp_info.libs = ['o2s']
