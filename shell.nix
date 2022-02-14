{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.clang_13
    pkgs.clang-tools
    pkgs.lld_13
    pkgs.lldb
    pkgs.ffmpeg-full
    pkgs.man
    pkgs.man-pages

    # keep this line if you use bash
    pkgs.bashInteractive
  ];
}
