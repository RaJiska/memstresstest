FROM alpine

WORKDIR /opt/memstresstest
COPY . .
RUN apk add --no-cache musl-dev make gcc
RUN make

FROM alpine

WORKDIR /opt/memstresstest
COPY --from=0 /opt/memstresstest/memstresstest .

ENTRYPOINT ["/opt/memstresstest"]
