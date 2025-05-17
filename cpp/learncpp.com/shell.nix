{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc gdb valgrind
    clang-tools clang bear
    cowsay
  ];
  env = {
    TEST="Hello there...";
  };
  shellHook = ''
    cowsay $TEST
  '';
}
