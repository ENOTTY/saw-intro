FROM ubuntu:20.04

# Configure the container environment

RUN apt-get update -qq && apt-get install -y -qq \
    vim-tiny \
    gdb \ 
    iputils-ping \
    netcat \
    wget \
    curl \
    zip unzip \
    curl \
    make

## Fixes a tzdata configuration issue in Ubuntu containers
ENV TZ=UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install Z3
#WORKDIR /opt
#RUN curl --silent --show-error -LO https://github.com/Z3Prover/z3/releases/download/z3-4.8.12/z3-4.8.12-x64-glibc-2.31.zip \
#    && unzip -q z3-4.8.12-x64-glibc-2.31.zip \
#    && ln -s z3-4.8.12-x64-glibc-2.31 z3 \
#    && rm z3-4.8.12-x64-glibc-2.31.zip
RUN apt-get update -qq && apt-get install -y -qq z3

# Install Yices
WORKDIR /opt
RUN curl --silent --show-error -L https://yices.csl.sri.com/releases/2.6.2/yices-2.6.2-x86_64-pc-linux-gnu-static-gmp.tar.gz | tar xz \
    && ln -s yices-2.6.2 yices

# Install SAW
WORKDIR /opt
RUN apt-get update -qq && apt-get install -y -qq \
     libtinfo5 clang
RUN curl --silent --show-error -L https://github.com/GaloisInc/saw-script/releases/download/v0.8/saw-0.8-Linux-x86_64.tar.gz | tar -xz \
    && ln -s saw-0.8-Linux-x86_64 saw

# Setup entry point with runtime environment variables
WORKDIR /
COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
