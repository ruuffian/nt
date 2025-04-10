{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
    ruff
    (python3.withPackages(p: with p; [
      numpy
    ]))
  ];
}
