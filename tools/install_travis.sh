#!/usr/bin/env bash

# Echo each command
set -x

# Exit on error.
set -e

if [[ "${PYKEP_BUILD}" != manylinux* ]]; then
    export deps_dir=$HOME/local
    export PATH="$HOME/miniconda/bin:$PATH"
    export PATH="$deps_dir/bin:$PATH"
fi

if [[ "${PYKEP_BUILD}" == "ReleaseGCC" ]]; then
    cmake -DCMAKE_PREFIX_PATH=$deps_dir -DBoost_NO_BOOST_CMAKE=ON -DCMAKE_BUILD_TYPE=Release -DPYKEP_BUILD_KEP_TOOLBOX=yes -DPYKEP_BUILD_TESTS=yes -DCMAKE_CXX_FLAGS="-fuse-ld=gold" ../;
    make -j2 VERBOSE=1;
    ctest -VV;
elif [[ "${PYKEP_BUILD}" == "DebugGCC" ]]; then
    cmake -DCMAKE_PREFIX_PATH=$deps_dir -DBoost_NO_BOOST_CMAKE=ON -DCMAKE_BUILD_TYPE=Debug -DPYKEP_BUILD_KEP_TOOLBOX=yes -DPYKEP_BUILD_TESTS=yes -DCMAKE_CXX_FLAGS="-fsanitize=address -fuse-ld=gold" ../;
    make -j2 VERBOSE=1;
    LSAN_OPTIONS=suppressions=/home/travis/build/esa/pykep/tools/lsan.supp ctest -VV;
elif [[ "${PYKEP_BUILD}" == "CoverageGCC" ]]; then
    cmake -DCMAKE_PREFIX_PATH=$deps_dir -DBoost_NO_BOOST_CMAKE=ON -DCMAKE_BUILD_TYPE=Debug -DPYKEP_BUILD_KEP_TOOLBOX=yes -DPYKEP_BUILD_TESTS=yes -DCMAKE_CXX_FLAGS="--coverage -fuse-ld=gold" ../;
    make -j2 VERBOSE=1;
    ctest -VV;
    bash <(curl -s https://codecov.io/bash) -x gcov-5;
elif [[ "${PYKEP_BUILD}" == Python* ]]; then
    # Install dcgp
    cmake -DCMAKE_INSTALL_PREFIX=$deps_dir -DCMAKE_PREFIX_PATH=$deps_dir -DBoost_NO_BOOST_CMAKE=ON -DCMAKE_BUILD_TYPE=Release -DPYKEP_BUILD_KEP_TOOLBOX=yes -DPYKEP_BUILD_TESTS=no ../; 
    make install VERBOSE=1;
    # Install dcgpy.
    cmake -DCMAKE_INSTALL_PREFIX=$deps_dir -DCMAKE_PREFIX_PATH=$deps_dir -DBoost_NO_BOOST_CMAKE=ON -DCMAKE_BUILD_TYPE=Release -DPYKEP_BUILD_KEP_TOOLBOX=no -DPYKEP_BUILD_PYKEP=yes ../; 
    make install VERBOSE=1;
    # Move out of the build dir.
    cd ../tools 
    # Run the test suite
    python -c "from pykep import test; test.run_test_suite()";
elif [[ "${PYKEP_BUILD}" == manylinux* ]]; then
    cd ..;
    docker pull ${DOCKER_IMAGE};
    docker run --rm -e TWINE_PASSWORD -e PYKEP_BUILD -e TRAVIS_TAG -v `pwd`:/pykep $DOCKER_IMAGE bash /pykep/tools/install_docker.sh
fi
 
set +e
set +x
