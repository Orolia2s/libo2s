const std = @import("std");

// NOTE: waiting for https://github.com/ziglang/zig/pull/20510
// const PACKAGE = @import("build.zig.zon");
const NAME = "o2s";
const VERSION = std.mem.trim(u8, @embedFile("version.txt"), &std.ascii.whitespace);

fn buildLibSourceFiles(b: *std.Build) !std.Build.Module.AddCSourceFilesOptions {
    var source_files = std.ArrayList([]const u8).init(b.allocator);
    defer source_files.deinit();
    {
        var src = try std.fs.openDirAbsolute(b.pathFromRoot(SRC_DIR), .{ .iterate = true });
        var walker = try src.walk(b.allocator);
        defer walker.deinit();

        while (try walker.next()) |entry| {
            if (entry.kind == .file and std.mem.eql(u8, std.fs.path.extension(entry.basename), ".c")) {
                try source_files.append(b.dupe(entry.path));
            }
        }
    }

    return .{
        .root = b.path(SRC_DIR),
        .files = b.dupeStrings(source_files.items),
        .flags = &(CFLAGS),
    };
}

pub fn build(b: *std.Build) !void {
    const semver = try std.SemanticVersion.parse(VERSION);
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const include = b.path(INCLUDE_DIR);

    const lib = b.addStaticLibrary(.{
        .name = NAME,
        .version = semver,
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    lib.root_module.addCMacro("LIBO2S_VERSION", VERSION);
    lib.addIncludePath(include);
    lib.addCSourceFiles(try buildLibSourceFiles(b));

    lib.installHeadersDirectory(b.path("include/o2s"), "o2s", .{});
    b.installArtifact(lib);

    { // Test
        const test_step = b.step("test", "Run tests");
        const test_exe = b.addExecutable(.{ .name = "test_libo2s", .target = target, .optimize = optimize });
        const run_test = b.addRunArtifact(test_exe);
        const catch2 = b.dependency("catch2", .{ .target = target, .optimize = optimize });

        test_exe.addCSourceFiles(.{
            .root = b.path(TEST_DIR),
            .files = &TEST_SOURCES,
            .flags = &.{"--std=c++23"},
        });
        test_exe.linkLibCpp();
        test_exe.linkLibrary(lib);
        test_exe.linkLibrary(catch2.artifact("Catch2"));
        test_exe.linkLibrary(catch2.artifact("Catch2WithMain"));
        test_step.dependOn(&run_test.step);
        const test_install = b.step("install_test", "Build tests");
        const install_test = b.addInstallArtifact(test_exe, .{});
        test_install.dependOn(&install_test.step);
    }
    { // Documentation
        const doc_step = b.step("doc", "Generate the documentation as a static website");
        const run_doxygen = b.addSystemCommand(&.{"doxygen"});

        run_doxygen.addFileArg(b.path("doc/Doxyfile.cfg"));
        run_doxygen.setEnvironmentVariable("PROJECT_VERSION", VERSION);
        doc_step.dependOn(&run_doxygen.step);
    }
    { // Freestanding subset
        const bare_step = b.step("micro", "Compile a subset of the library for a freestanding target");
        const bare_target = b.resolveTargetQuery(.{
            .cpu_arch = .arm,
            .os_tag = .freestanding,
            .abi = .eabi,
        });
        const bare_lib = b.addStaticLibrary(.{
            .name = "micro2s",
            .version = semver,
            .target = bare_target,
            .optimize = .ReleaseSmall,
        });
        bare_lib.addIncludePath(include);
        bare_lib.addIncludePath(b.path("include/micro"));
        bare_lib.addCSourceFiles(.{ .root = b.path("src/deque"), .files = &.{
            "init_clear.c", "getters.c",
            "internals.c",  "pop.c",
            "push.c",
        } });
        bare_lib.addCSourceFiles(.{ .root = b.path("src"), .files = &.{
            "stream/input.c",
            "queue.c",
        } });
        bare_lib.installHeadersDirectory(b.path("include/o2s"), "o2s", .{
            .include_extensions = &.{
                "deque.h",         "queue.h",
                "stack.h",         "input_stream.h",
                "preprocessing.h", "private_prepro.h",
            },
            .exclude_extensions = &.{
                "string_input_stream.h",
                "file_input_stream.h",
            },
        });
        bare_step.dependOn(&b.addInstallArtifact(bare_lib, .{}).step);
    }
}

const SRC_DIR = "src";
const INCLUDE_DIR = "include";
const TEST_DIR = "test";

const CFLAGS = .{
    "--std=gnu23",
    "-Wall",
    "-Wextra",
    "-Werror",
    // "-Wvla",
    "-Wformat=2",
    "-Wmissing-prototypes",
    "-Wmissing-declarations",
    "-Wold-style-definition",
    "-Wstrict-prototypes",
};

const TEST_SOURCES = .{
    "array.cpp",
    "deque.cpp",
    "file.cpp",
    "hashes.cpp",
    "input_stream.cpp",
    "mutex.cpp",
    "serial.cpp",
    "string.cpp",
    "thread.cpp",
    "timer.cpp",
    "to_string.cpp",
    "version.cpp",
    "write.cpp",
};
