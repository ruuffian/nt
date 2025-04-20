{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
    ruff
    basedpyright
    (python3.withPackages(p: with p; [
      numpy
    ]))
  ];
}
