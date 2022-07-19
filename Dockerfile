FROM ubuntu:22.04
ENV TZ=Asia/Seoul
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt update
RUN apt install --assume-yes pkg-config
RUN apt install -y git build-essential meson m4 gperf libcap-dev libmount-dev python3-jinja2 gdb dbus vim
RUN git clone http://github.com/dlwogns312/systemd_debug.git /home/systemd_debug
COPY ./.vscode/ /home/systemd_debug/.vscode
WORKDIR "/home/systemd_debug"
RUN meson build/ --buildtype=debug
WORKDIR "/home/systemd_debug/build"
RUN ninja
RUN meson install
