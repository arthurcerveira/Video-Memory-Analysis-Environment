FROM python:3

WORKDIR /usr/src/mem-analysis

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt

RUN apt-get update
RUN apt-get install cmake -y

RUN apt-get upgrade make cmake gcc g++

COPY . .

RUN bash setup.sh

CMD [ "bash", "./analysis_init.sh" ]
