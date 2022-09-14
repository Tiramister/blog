#!/bin/bash

function copy_file() {
  src_path="$1"
  dst_path="$2"

  mkdir -p $(dirname "${dst_path}")

  if [[ "${src_path}" == *.md ]]; then
    echo "${src_path} -> ${dst_path}"
    cat "${src_path}" | python3 invert.py | prettier --stdin-filepath x.md > "${dst_path}"
  else
    cp "${src_path}" "${dst_path}"
  fi
}

function main() {
  src_dir="$1"
  dst_dir="$2"

  find "${src_dir}" -type f | while read -r src_path; do
    dst_path=$(echo ${src_path} | sed -e "s:${src_dir}:${dst_dir}:g")
    copy_file "${src_path}" "${dst_path}"
  done
}

main ../content/posts ../original/posts
