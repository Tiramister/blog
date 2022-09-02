#!/bin/zsh
DIR=$1

if [ -z "${DIR}" ]; then
  echo "[ERROR] Pass the directory name as an argument."
  exit 1
fi

if [ -d "${DIR}" ]; then
  rm -rf "${DIR}"
fi

mkdir "${DIR}" && \
cd "${DIR}" && \
  pbpaste | \
  prettier --stdin-filepath x.md | \
  python3 ../../../convert.py | \
  prettier --stdin-filepath x.md > index.md && \
code index.md && \
cd ..
