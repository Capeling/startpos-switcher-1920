export SPLAT_DIR=~/Documents/1.9/sdk/splat
export TOOLCHAIN=~/Documents/1.9/sdk/toolchain/clang-cl-msvc.cmake
export HOST_ARCH=x86
export GEODE_SDK=/home/capeling/Documents/1.9/geode
export GEODE_BINDINGS_REPO_PATH=/home/capeling/Documents/geode_bindings

cmake \
    -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -Bbuild \
    -GNinja

cmake --build build --config RelWithDebInfo
