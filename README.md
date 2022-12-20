# ze-count-engines

A simple utility to count the number of compute and copy engines on Intel GPUs.

## Setup

1. Clone repository with submodules
    ```bash
    git clone https://github.com/lisanna-dettwyler/ze-count-engines.git --recurse-submodules
    ```

2. Install intel-compute-runtime
    ```bash
    mkdir neo
    cd neo
    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.12260.1/intel-igc-core_1.0.12260.1_amd64.deb
    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.12260.1/intel-igc-opencl_1.0.12260.1_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/22.43.24558/intel-level-zero-gpu-dbgsym_1.3.24558_amd64.ddeb
    wget https://github.com/intel/compute-runtime/releases/download/22.43.24558/intel-level-zero-gpu_1.3.24558_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/22.43.24558/intel-opencl-icd-dbgsym_22.43.24558_amd64.ddeb
    wget https://github.com/intel/compute-runtime/releases/download/22.43.24558/intel-opencl-icd_22.43.24558_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/22.43.24558/libigdgmm12_22.2.0_amd64.deb
    sudo dpkg -i ./*
    cd -
    rm -rf neo
    ```

3. Build
    ```bash
    make
    ```

4. Add user to render and video groups
    1. ```bash
        sudo usermod -aG render,video $USER
        ```
    2. Logout and then log back in to register the new groups
    (alternatively, you may run ./ze-count-engines as root)

## Usage

```bash
./ze-count-engines
```