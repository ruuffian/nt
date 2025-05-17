{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [ gcc clang-tools clang bear ];
  buildInputs = with pkgs; [
    cowsay
  ];
  env = {
    TEST="Hello there...";
  };
  shellHook = ''
    cowsay $TEST
  '';
}
