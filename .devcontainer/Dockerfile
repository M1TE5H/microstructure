FROM ubuntu:latest
# RUN apt-get upgrade
# RUN apt-get build-essential
RUN apt-get update

RUN apt-get install -y sudo git gcc g++ make cmake gnuplot texlive-xelatex python3.8 ruby-full

ENV PATH=/usr/bin/gcc:$PATH
ENV PATH=/usr/bin/cmake:$PATH

RUN cmake --version

# RUN git clone https://www.github.com/M1TE5H/microstructure

WORKDIR /microstructure/
COPY . /microstructure
RUN sh scripts/automate.sh
CMD [ "./build/applications/metal" ]