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

    lib.installHeadersDirectory(include, "", .{});
    b.installArtifact(lib);
}

const SRC_DIR = "src";
const INCLUDE_DIR = "include";

const CFLAGS = .{
    "--std=gnu23",
    "-Wall",
    "-Wextra",
    "-Wvla",
    "-Wformat=2",
    "-Wmissing-prototypes",
    "-Wmissing-declarations",
    "-Wold-style-definition",
    "-Wstrict-prototypes",
    "-fno-sanitize=undefined", // NOTE: disable UndefinedBehaviorSanitizer
};
