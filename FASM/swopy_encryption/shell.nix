{ pkgs ? import <nixpkgs> {} }:
	pkgs.mkShell {
		nativeBuildInputs = with pkgs; [
			fasm
		];
		shellHook = ''
		'';
}
