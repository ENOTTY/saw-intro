# Quick start
We use SAW to check a few implementations of pop count, as described in the
[SAW intro](https://saw.galois.com/intro/IntroToSAW.html).

The idea behind this workflow is that a human will use SAW to help them compare
an implementation of pop count to the canonical or correct version of pop count.

In English, we would describe the pop count function as counting the number of
bits set to `1` in an integer when it is represented in binary.

The implementations of pop count in this repo are as follows:
* `pop_count` - Optimized version from the Hacker's Delight book
* `pop_count_ok` - An extremely-slow version that iterates through each bit
  and checks if it is set to `1`.
* `pop_spec` - Essentially the same implementation as `pop_count_ok`, but for
  the purposes of this exercise, it is considered the "correct" version of the
  pop count function. In practice, a human would look at this function, and
  declare it to have correctly implemented pop count, and it would become the
  benchmark against which to compare all other implementations of pop count.
  Since this implementation is intended to be human-readable, it is written in
  an easy-to-understand way. For example, compare the readability of `pop_spec`
  to the readbility to `pop_count`.
* `pop_count_broken1` - This implementation is broken in a (visually) subtle
  way, missing a single operator when incrementing the count. That said, it
  would be trivially detectable via testing.
* `pop_count_broken2` - This implementation demonstrates that testing is not
  sufficient. It returns the correct value for all inputs except `0xDEADBEEF`.
  If you are using random testing, that input has a 1/2^32 chance of being
  randomly generated. Good luck.
* `pop_count_broken3` - This implementation is similar to `pop_count_ok`, but
  broken in a (visually) and semantically subtle way. In the broken
  implementation, `mask` is declared as an 8-bit integer, which is too small to
  hold the mask used to check bits 8-31 of the input. As a result, this
  implementation will return the incorrect result for all integers at or above 2^8.

For correct implementations (according to the spec), SAW will declare "Proof
succeeded!"

For the incorrect implmentations, SAW will declare "Proof failed" and give you a
counter-example.

SAW is scripted using the `popcounts.saw` file. SAW stops processing the file
on the first failure, so you will need to reorder the checks of the broken
functions in order to try them out.

# Docker
Build the container with:
```
docker build . -f Dockerfile -t sawdev
```

If using Amazon Linux 2, you may need to add --network=host

Run the container with:
```
docker run --network=host --rm --mount type=bind,source="$(pwd)",target=/workspace -it sawdev /bin/bash
```

Once you have a shell in the container, run the examples with:
```
cd /workspace && saw popcounts.saw
```

If the container is broken for some reason, use [SAW's Dockerfile](https://github.com/GaloisInc/saw-script/blob/master/saw/Dockerfile)
as inspiration
