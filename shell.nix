{
  system ? builtins.currentSystem,
  pkgs ? import <nixpkgs> { inherit system; },
}: pkgs.mkShell.override { stdenv = pkgs.llvmPackages_16.stdenv; } {
  packages = with pkgs; [
    llvmPackages_16.libllvm
    gcc13
    lcov
  ];

  buildInputs = with pkgs; [
    catch2_3
  ];
}
