#!/usr/bin/python3

from io import BufferedWriter
from struct import pack
import os
import sys

HEADER = b"\x2e\x4d\x44\x4c"

def write_header(file: BufferedWriter, vertices_count: int, indices_count: int, vertices_offset: int, indices_offset: int):
    file.write(HEADER) # header
    file.write(vertices_count.to_bytes(4, byteorder="big"))
    file.write(indices_count.to_bytes(4, byteorder="big"))
    file.write(vertices_offset.to_bytes(4, byteorder="big"))
    file.write(indices_offset.to_bytes(4, byteorder="big"))

def parse_vertex(vertex: list[str]) -> list[float]:
    return [float(s) for s in vertex]

def parse_face(face: list[str]) -> list[int]:
    return [int(s) for v in face for s in v.split('/')]

def parse_obj(file: str) -> tuple[list[float], list[int]]:
    vertices = []
    indices = []
    with open(file, "rt") as f:
        for line in f.readlines():
            spl = line.split()
            if not line:
                continue
            cmd = spl[0]
            if cmd == "v":
                vertices.extend(parse_vertex(spl[1:]))
            elif cmd == "f":
                indices.extend(parse_face(spl[1:]))

    return (vertices, indices,)

if len(sys.argv) < 2:
    print("Not enough args.")
    exit(1)

file_name = sys.argv[1]

with open(os.path.splitext(file_name)[0], "wb") as f:
    vertices, indices = parse_obj(file_name)
    write_header(f, len(vertices), len(indices), len(HEADER) + 0, len(HEADER) + len(vertices))
    [f.write(pack("<f", v)) for v in vertices]
    [f.write(i.to_bytes(4, byteorder="big")) for i in indices]
