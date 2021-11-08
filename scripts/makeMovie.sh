

ffmpeg -framerate 24 -i ./build/render.%04d.bmp -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p -y ./build/render.mp4
ffmpeg -i ./build/render.mp4 -vf "fps=24,scale=720:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse"  -y ./build/render.gif
rm ./build/render.*.bmp
