{
  description = "Fundamental datastructures for C";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs.url = "github:nixos/nixpkgs/23.05";
  };

  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        version = pkgs.lib.fileContents ./version.txt;
        src = pkgs.nix-gitignore.gitignoreSource [ ] ./.;
      in {
        packages = rec {
          libo2s = pkgs.llvmPackages_16.stdenv.mkDerivation (self: {
            pname = "libo2s";
            inherit version;
            outputs = [ "out" "doc" "ci" ];

            inherit src;
            nativeBuildInputs = with pkgs; [
              pkg-config
              doxygen
              validatePkgConfig
            ];
            checkInputs = with pkgs; [ catch2_3 ];

            Version = self.version;
            doCheck = true;

            buildPhase = ''
              runHook preBuild

              make static
              make doc/html/index.html

              runHook postBuild
            '';
            checkPhase = ''
              runHook preCheck

              make -C test build
              ./test/test_libo2s.exe --reporter junit > report.xml

              runHook postCheck
            '';
            installPhase = ''
              runHook preInstall

              install -Dm644 -t $out/lib ${self.pname}.a
              install -Dm644 -t $out/share/pkgconfig ${self.pname}.pc
              sed -i -e "s|[$]out|$out|g" -e 's|[$]Version|${self.Version}|g' $out/share/pkgconfig/${self.pname}.pc
              install -Dm644 -t $ci report.xml
              mkdir --parents $out/include $doc/share/doc
              cp --recursive include/o2s $out/include
              cp --recursive doc/html $doc/share/doc

              runHook postInstall
            '';

            passthru.tests.pkg-config =
              pkgs.testers.testMetaPkgConfig self.finalPackage;
            meta.pkgConfigModules = [ "libo2s" ];
          });
          libo2s-cov = pkgs.llvmPackages_16.stdenv.mkDerivation (self: {
            pname = "libo2s-cov";
            inherit version;

            inherit src;
            buildInputs = with pkgs; [ catch2_3 ];
            nativeBuildInputs = with pkgs; [ pkg-config kcov ];

            Version = self.version;
            dontInstall = true;

            preBuild = ''
              makeFlagsArray+=(CFLAGS='-O0 -g')
            '';
            buildPhase = ''
              runHook preBuild

              make static
              make -C test build
              kcov --include-pattern=$PWD/src $out ./test/test_libo2s.exe

              runHook postBuild
            '';
          });
          default = libo2s;
        };

        devShells.default =
          pkgs.mkShell.override { stdenv = pkgs.llvmPackages_16.stdenv; } {
            packages = with pkgs; [ pkg-config doxygen kcov ];
            buildInputs = with pkgs; [ catch2_3 ];
          };
      });
}
