cmake -S . -B build \
  -DOmega_h_ROOT=/lore/hasanm4/wsources/omega_h_scorec/install \
  -DKokkos_ROOT=/lore/hasanm4/Kokkos/kokkosInstallrhel9omp/ \
  -DCMAKE_INSTALL_PREFIX=build/install

cmake --build build --parallel 8 --target install
