{
  description = "Fundamental datastructures for C";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs.url = "github:nixos/nixpkgs/23.05";
  };

  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = nixpkgs.legacyPackages.${system};
      in {
        packages = rec {
          libo2s = pkgs.llvmPackages_16.stdenv.mkDerivation (self: {
            name = "libo2s";
            outputs = [ "out" "doc" ];

            src = pkgs.nix-gitignore.gitignoreSource [ ] ./.;
            nativeBuildInputs = with pkgs; [
              pkg-config
              doxygen
              validatePkgConfig
            ];

            Version = "nix";

            buildPhase = ''
              runHook preBuild

              make static
              make doc/html/index.html

              runHook postBuild
            '';

            installPhase = ''
              runHook preInstall

              install -Dm644 -t $out/lib ${self.name}.a
              install -Dm644 -t $out/share/pkgconfig ${self.name}.pc
              sed -i -e "s|[$]out|$out|g" -e 's|[$]Version|${self.Version}|g' $out/share/pkgconfig/${self.name}.pc
              mkdir --parents $out/include $doc/share/doc
              cp --recursive include/o2s $out/include
              cp --recursive doc/html $doc/share/doc

              runHook postInstall
            '';

            passthru.tests.pkg-config =
              pkgs.testers.testMetaPkgConfig self.finalPackage;
            meta.pkgConfigModules = [ "libo2s" ];
          });
          default = libo2s;
        };

        devShells.default =
          pkgs.mkShell.override { stdenv = pkgs.llvmPackages_16.stdenv; } {
            packages = with pkgs; [
              llvmPackages_16.libllvm
              gcc13
              pkg-config
              lcov
            ];
            buildInputs = with pkgs; [ catch2_3 conan ];
          };
      });
}
