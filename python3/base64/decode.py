#!/usr/bin/python3

import sys

from lib import decode

with open(sys.argv[1], 'r') as fin:
    with open(sys.argv[2], 'wb') as fout:
        decode(fin, fout)
