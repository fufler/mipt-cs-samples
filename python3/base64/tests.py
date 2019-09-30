#!/usr/bin/python3

import unittest

from lib import encode_text, encode_binary, decode_as_binary, decode_as_text


class Encode(unittest.TestCase):

    def test_text(self):
        self.assertEqual('QQ==', encode_text('A'))
        self.assertEqual('QQo=', encode_text('A\n'))
        self.assertEqual('QUI=', encode_text('AB'))
        self.assertEqual('QUJD', encode_text('ABC'))

    def test_binary(self):
        self.assertEqual('AA==', encode_binary(b'\x00'))
        self.assertEqual('AAE=', encode_binary(b'\x00\x01'))
        self.assertEqual('AAEC', encode_binary(b'\x00\x01\x02'))


class Decode(unittest.TestCase):

    def test_binary(self):
        self.assertEqual(b'\x00', decode_as_binary('AA=='))
        self.assertEqual(b'\x00\x01', decode_as_binary('AAE='))
        self.assertEqual(b'\x00\x01\x02', decode_as_binary('AAEC'))

    def test_text(self):
        self.assertEqual('A', decode_as_text('QQ=='))
        self.assertEqual('A\n', decode_as_text('QQo='))
        self.assertEqual('AB', decode_as_text('QUI='))
        self.assertEqual('ABC', decode_as_text('QUJD'))


if __name__ == '__main__':
    unittest.main()
