project(
	'libo2s',
	'c', 'cpp',
	version: files('version.txt'),
	default_options: {
		'c_std': 'gnu23',
		'cpp_std': 'c++23',
	},
	meson_version: '>=1.2.0',
)

src = files(
	run_command(
		'find',
		join_paths(meson.current_source_dir(), 'src/'),
		'-type', 'f',
		'-name', '*.c',
		check: true,
	)
	.stdout()
	.strip()
	.splitlines()
)
inc = include_directories('include')
lib = library(
	'o2s',
	src,
	include_directories: inc,
)

libo2s_dep = declare_dependency(
	link_with: lib,
	include_directories: inc,
)
meson.override_dependency(meson.project_name(), libo2s_dep)

catch2_dep = dependency('catch2-with-main', fallback: ['catch2', 'catch2_with_main_dep'])

test_src = files(
	run_command(
		'find',
		join_paths(meson.current_source_dir(), 'test/'),
		'-type', 'f',
		'-name', '*.cpp',
		check: true,
	)
	.stdout()
	.strip()
	.splitlines()
)
test_exe = executable(
	'tests',
	test_src,
	dependencies: [
		libo2s_dep,
		catch2_dep,
	],
	cpp_args: [
		'-DCATCH_CONFIG_FAST_COMPILE',
	],
	build_by_default: false,
)
test('tests', test_exe)
