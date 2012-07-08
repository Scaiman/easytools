#!/bin/sh

qmake && make && gdb --eval-command=r ./SpriteVertexForm
