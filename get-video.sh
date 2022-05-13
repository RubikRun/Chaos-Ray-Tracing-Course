#!/bin/bash
ffmpeg -i anim/%4d.ppm -c:v libx264 -r 24 anim/anim.mp4
