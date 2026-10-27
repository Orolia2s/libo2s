project(
	'libo2s',
	'c',
	version: files('version.txt'),
	default_options: {
		'c_std': 'gnu23',
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
