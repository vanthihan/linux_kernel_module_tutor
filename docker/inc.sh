#!/bin/bash

source ./exec-cmd-arr.sh

PROJECT_NAME="kernel module learning"
#replace spaces with '-'
PROJECT_NAME_WITHOUT_SPACE=${PROJECT_NAME// /-}

export DOCKER_IMAGE_NAME="${PROJECT_NAME_WITHOUT_SPACE}-image"
export DOCKER_CONTAINER_NAME="${PROJECT_NAME_WITHOUT_SPACE}-container-1"

#Host and guest shared directories from you machine and docker
export HOST_SHARED_DIR="/home/thihanvan/samba/views/linux_kmod/"
export GUEST_MOUNT_POINT="/home/work_dir"
