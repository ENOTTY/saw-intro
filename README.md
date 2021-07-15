# Docker
Build the container with:
```
docker build . -f Dockerfile -t sawdev
```

If using Amazon Linux 2, may need to add --network=host

Run the container with:
```
docker run --network=host --rm --mount type=bind,source="$(pwd)",target=/workspace -it sawdev /bin/bash
```

If the container is broken for some reason, use this as inspiration https://github.com/GaloisInc/saw-script/blob/master/saw/Dockerfile
