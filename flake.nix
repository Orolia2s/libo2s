{
  description = "Fundamental datastructures for C";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/23.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      packages = rec {
        libo2s = import ./default.nix { inherit system pkgs; };
        default = libo2s;
      };
    }
  );
}
