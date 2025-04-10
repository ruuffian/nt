{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc gdb valgrind
    clang-tools clang bear
    cowsay
  ];
  shellHook = ''
    cowsay "Hello there..."
  '';
}
