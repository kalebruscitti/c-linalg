with (import <nixpkgs> {});
mkShell {
  buildInputs = [
    gcc
  ];
  shellHook = ''
  zsh
  '';
}
