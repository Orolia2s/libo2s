{
  system ? builtins.currentSystem,
  pkgs ? import <nixpkgs> { inherit system; },
}
: pkgs.llvmPackages_16.stdenv.mkDerivation rec
{
  pname = "libo2s";
  version = "0.4.1";
  outputs = [ "out" "doc" ];

  src =  pkgs.nix-gitignore.gitignoreSource [] ./.;
  nativeBuildInputs = with pkgs; [ doxygen ];


  Version = version;

  buildPhase = ''
    runHook preBuild

    if [ -n "$out" ]; then
      make static
    fi

    if [ -n "$doc" ]; then
      make doc/html/index.html
    fi

    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall

    if [ -n "$out" ]; then
      mkdir --parents $out/lib $out/include
      cp ${pname}.a $out/lib
      cp  --recursive include/o2s $out/include
    fi

    if [ -n "$doc" ]; then
      mkdir --parents $doc/share/doc
      cp --recursive doc/html $doc/share/doc
    fi

    runHook postInstall
  '';
}
