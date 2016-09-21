{ nixpkgs ? <nixpkgs>
, systems ? [ "i686-linux" "x86_64-linux" ]
, libiffJobset ? import ../libiff/release.nix { inherit nixpkgs systems officialRelease; }
, lib8svxJobset ? import ../lib8svx/release.nix { inherit nixpkgs systems officialRelease; }
, SDL_8SVX ? { outPath = ./.; rev = 1234; }
, officialRelease ? false

}:

let
  pkgs = import nixpkgs {};
  
  version = builtins.readFile ./version;
  
  jobs = rec {
    tarball =
      with pkgs;

      let
        libiff = builtins.getAttr (builtins.currentSystem) (libiffJobset.build);
        lib8svx = builtins.getAttr (builtins.currentSystem) (lib8svxJobset.build);
      in
      releaseTools.sourceTarball {
        name = "SDL_8SVX-tarball";
        src = SDL_8SVX;
        inherit version officialRelease;
        dontBuild = false;

        buildInputs = [ pkgconfig libiff lib8svx libresample SDL2 SDL2_mixer help2man ];
        LIBS = "-lgcc_s";
        CFLAGS = "-ansi -pedantic -Wall";
      };
      
    build =
      pkgs.lib.genAttrs systems (system:
        with import nixpkgs { inherit system; };
        
        let
          libiff = builtins.getAttr system (libiffJobset.build);
          lib8svx = builtins.getAttr system (lib8svxJobset.build);
        in
        releaseTools.nixBuild {
          name = "SDL_8SVX";
          inherit version;
          src = tarball;
          buildInputs = [ pkgconfig libiff lib8svx libresample SDL2 SDL2_mixer ];
          LIBS = "-lgcc_s";
          CFLAGS = "-ansi -pedantic -Wall";
        }
      );
  };
in
jobs
