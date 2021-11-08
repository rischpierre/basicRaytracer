



ffmpeg -framerate 24 -i ./build/render.%04d.bmp -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p -y ./build/render.mp4
rm ./build/render.*.bmp
xdg-open ./build/render.mp4