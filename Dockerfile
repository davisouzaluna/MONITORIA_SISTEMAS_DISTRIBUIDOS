FROM ubuntu:22.04

LABEL maintainer="Sdavi@gmail.com"

RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    uuid-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app


COPY . /app

RUN mkdir build && cd build && cmake .. && make
CMD ["bash"]
