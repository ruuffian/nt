{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc gdb valgrind
    cowsay
  ];
  shellHook = ''
    cowsay "Hello there..."
  '';
}
