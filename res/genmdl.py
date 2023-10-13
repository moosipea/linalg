#!/usr/bin/python3

with open("out.mdl", "wb") as f:
    f.write(b"\x2e\x4d\x44\x4c") # ".MDL"
    f.write(b"\x00\x00\x00\x00")
    f.write(b"\x00\x00\x00\x00")
    f.write(b"\x00\x00\x00\x00")
    f.write(b"\x00\x00\x00\x00")
