{
  description = "JPam module";
  inputs = {
    nixpkgs.url = github:nixos/nixpkgs/nixpkgs-unstable;
    utils.url = github:numtide/flake-utils;
  };
  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; };
      in {
        devShell = with pkgs; mkShell {
          packages = [
            linux-pam
            clang-tools
            gnumake
            pamtester
          ];
        };
      });
}
      
