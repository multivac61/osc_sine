{
  description = "OSC sine wave sender";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        packages.default = pkgs.stdenv.mkDerivation {
          name = "osc_sine";
          src = ./.;

          buildInputs = [ pkgs.liblo ];

          nativeBuildInputs = [ pkgs.pkg-config ];

          buildPhase = ''
            $CC osc_sine.c -o osc_sine -llo -lm
          '';

          installPhase = ''
            mkdir -p $out/bin
            mv osc_sine $out/bin/
          '';
        };
        apps.default = {
          type = "app";
          program = "${self.packages.${system}.default}/bin/osc_sine";
        };
      }
    );
}
