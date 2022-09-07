#!/bin/bash
DIR=$1
SCRIPT_DIR=$(realpath $(dirname "$0"))

if [ -z "${DIR}" ]; then
  echo "[ERROR] Pass the directory name as an argument."
  exit 1
fi

if [ -d "${DIR}" ]; then
  rm -r "${DIR}"
fi

mkdir -p "${DIR}" && \
cd "${DIR}" && \
  cat - | \
  prettier --stdin-filepath x.md | \
  python3 ${SCRIPT_DIR}/convert.py | \
  prettier --stdin-filepath x.md > index.md && \
code index.md && \
cd ..
