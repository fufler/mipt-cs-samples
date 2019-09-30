#!/usr/bin/python3

import sys

from lib import encode

with open(sys.argv[1], 'rb') as fin:
    with open(sys.argv[2], 'w') as fout:
        encode(fin, fout)
