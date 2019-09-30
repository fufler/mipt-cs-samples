from string import ascii_lowercase, ascii_uppercase, digits
import io
import re

ALPHABET = ascii_uppercase + ascii_lowercase + digits + '+/'
BASE64_RE = re.compile('^[a-zA-Z0-9+/]{2,4}={,2}$')


def encode(fin, fout):
    while True:
        b = fin.read(3)

        if len(b) == 0:
            break

        if len(b) == 3:
            padding = 0
        else:
            padding = 1 if len(b) == 2 else 2
            b += b'\x00'

        fout.write(ALPHABET[b[0] >> 2])
        fout.write(ALPHABET[((b[0] & 3) << 4) | (b[1] >> 4)])

        if padding == 2:
            fout.write('==')
            break

        fout.write(ALPHABET[((b[1] & 15) << 2) | (b[2] >> 6)])

        if padding == 1:
            fout.write('=')
            break

        fout.write(ALPHABET[b[2] & 63])


def decode(fin, fout):
    while True:
        s = fin.read(4)

        if s == '':
            break

        if len(s) != 4:
            raise Exception('Input is trucncated')

        if BASE64_RE.match(s) is None:
            raise Exception('Input is invalid')

        if s[-2:] == '==':
            padding = 2
        elif s[-1] == '=':
            padding = 1
        else:
            padding = 0

        x1, x2, x3, x4 = map(ALPHABET.find, s)

        b = bytes([(x1 << 2) | (x2 >> 4)])

        if padding < 2:
            b += bytes([((x2 & 15) << 4) | (x3 >> 2)])

            if padding == 0:
                b += bytes([((x3 & 3) << 6) | x4])

        fout.write(b)


def encode_binary(input_data):
    with io.BytesIO(input_data) as fin:
        with io.StringIO() as fout:
            encode(fin, fout)
            return fout.getvalue()


def encode_text(input_data):
    return encode_binary(input_data.encode())


def decode_as_binary(input_data):
    with io.StringIO(input_data) as fin:
        with io.BytesIO() as fout:
            decode(fin, fout)
            return fout.getvalue()


def decode_as_text(input_data):
    return decode_as_binary(input_data).decode()
