#!/bin/bash

if [[ -z "$1" ]]; then echo "Usage: $0 <dirname>"; exit 1; fi

cp -r .template $1
