#!/bin/env bash


default_install_path="$HOME/.local/bin/"

if [ -n "$1" ]; then
  install_path="$1"
else
  install_path="$default_install_path"
fi

gcc -o ./color ./color.c -lm

if [ $? -eq 0 ]; then
  mv color "$install_path"
  if [ $? -eq 0 ]; then
    echo "color-cli has been successfully installed."
  else
    echo "color-cli installation has failed."
  fi
else
  echo "color-cli compilation has failed."
fi


