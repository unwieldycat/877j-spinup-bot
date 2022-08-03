#!/bin/bash
echo "$(tput setaf 5)Running Make...$(tput setaf 7)"
make

echo "$(tput setaf 5)Uploading to Brain...$(tput setaf 7)"
pros upload