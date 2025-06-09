@@echo off
set DISPLAY=host.docker.internal:0

docker build -t qt-app .

docker run -it --rm ^
  -e DISPLAY=host.docker.internal:0 ^
  -v /tmp/.X11-unix:/tmp/.X11-unix ^
  --name qt_gui_app ^
  qt_project_image_name


