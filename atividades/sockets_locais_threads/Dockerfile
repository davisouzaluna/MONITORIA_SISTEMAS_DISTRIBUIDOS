FROM ubuntu:24.04

WORKDIR /app

# Atualizacao
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    uuid-dev \
    pthreads \
    && rm -rf /var/lib/apt/lists/*

COPY . .

# Build
RUN mkdir build
WORKDIR /app/build
RUN cmake ..
RUN make

# ENTRYPOINT ["./ServerClientApp"]