#!/bin/bash
scp src/cat/s21_cat deploy:/usr/local/bin
if [[ $? -ne 0 ]]; then exit 1; fi
scp src/grep/s21_grep deploy:/usr/local/bin
if [[ $? -ne 0 ]]; then exit 1; fi
