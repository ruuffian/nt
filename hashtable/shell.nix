{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc gdb valgrind
    clang-tools clang bear
    cowsay
  ];
  shellHook = ''
    export LD_LIBRARY_PATH="./lib:/usr/local/lib:$LD_LIBRARY_PATH"
    cowsay "Hello there..."
  '';
}
