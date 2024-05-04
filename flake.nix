{
    description = "sukima development environment";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    };

    outputs = { self , nixpkgs ,... }: {
        devShells.x86_64-linux.default = let
            pkgs = import nixpkgs {
                system = "x86_64-linux";
            };
            kernel = pkgs.linuxKernel.packages.linux_6_6.kernel;
        in pkgs.mkShell {
            packages = with pkgs; [
                kernel.dev
                bear
                clang-tools
                gnumake
                pkg-config
            ];

            shellHook = ''
                export LINUX_KERNEL_PATH=${kernel.dev}
                exec fish
            '';
        };
    };
}
